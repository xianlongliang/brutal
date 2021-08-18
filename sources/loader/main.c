#include <brutal/alloc.h>
#include <brutal/io.h>
#include <brutal/log.h>
#include <efi/lib.h>
#include <efi/srvs.h>
#include <efi/tty.h>
#include <elf/elf.h>
#include "loader/config.h"
#include "loader/protocol.h"

void __chkstk() { return; }

char *logo[] = {
    "/yyyyo:yyyys  `:osys/.",
    "  -hMMd .yMMN oNMMNmMMMh.",
    "   -hd   .yNyMMy.  `+MMm`",
    "/sssss:ssssyNMM`     dMM-",
    "  :dMMd -hMMNoMMh:` .sMMd",
    "   :dd   -hN /mMMMMMMNs`                 Press Enter to boot",
    ".+++++y+++++y+++ydhdd+`                  Press ESC to shutdown",
    ":MMMMMMMMMMMMMMMd: dMMNs`",
    ":MMh     `MMMMd:   dMMMMd",
    ":MMh      MMMy/////mMMMMM-",
    ":MMh      MMNyMMMMMMMMMMm`",
    ":MMNmmmmmmMMN sNMMMMMMMh.",
    ".yyyyyyyyyyys  `/oyys+.",
};

void loader_splash(void)
{
    efi_tty_set_attribute(EFI_BLUE);

    print(io_std_out(), "Brutal boot\n");

    efi_tty_set_attribute(EFI_WHITE);

    for (size_t i = 0; i < sizeof(logo) / sizeof(*logo); i++)
    {
        print(io_std_out(), "{}\n", logo[i]);
    }
}

void loader_load(Elf64Header const *elf_header, void *base)
{
    Elf64ProgramHeader *prog_header = (Elf64ProgramHeader *)(base + elf_header->program_header_table_file_offset);

    for (int i = 0; i < elf_header->program_header_table_entry_count; i++)
    {
        if (prog_header->type == ELF_PROGRAM_HEADER_LOAD)
        {
            void *file_segment = (void *)((uint64_t)base + prog_header->file_offset);
            void *mem_segment = (void *)prog_header->virtual_address;

            mem_cpy(mem_segment, file_segment, prog_header->file_size);

            void *extra_zeroes = mem_segment + prog_header->file_size;
            uint64_t extra_zeroes_count = prog_header->memory_size - prog_header->file_size;

            if (extra_zeroes_count > 0)
            {
                mem_set(extra_zeroes, 0x00, extra_zeroes_count);
            }
        }

        prog_header = (Elf64ProgramHeader *)((void *)prog_header + elf_header->program_header_table_entry_size);
    }
}

uintptr_t loader_load_kernel(Str path)
{
    IoFile file;
    IoFileReader reader;
    Buffer buffer;

    log("Loading elf file...");
    io_file_open(&file, path);
    reader = io_file_read(&file);
    buffer = io_readall(base_cast(&reader), alloc_global());

    Elf64Header *header = (Elf64Header *)buffer.data;

    if (buffer.used < sizeof(Elf64Header) ||
        !elf_validate(header))
    {
        panic("Invalid elf file!");
    }

    log("Elf file loaded in memory, mapping it...");

    loader_load(header, buffer.data);

    uintptr_t entry = header->entry;

    buffer_deinit(&buffer);

    log("Entry is {#x}", entry);

    return entry;
}

void loader_boot(LoaderEntry *entry)
{
    log("Loading kernel...");

    uintptr_t entry_point = loader_load_kernel(entry->kernel);

    log("Kernel loaded, jumping in to it...");

    Handover handover = get_handover();

    asm volatile(
        "mov %0, %%rdi\n"
        "mov %1, %%rsi\n"
        "mov %2, %%rax\n"
        "call *%%rax\n" ::"a"(&handover),
        "b"((uint64_t)0xC001B001), "c"((uint64_t)entry_point));

    assert_unreachable();
}

void loader_menu(void)
{
    EFIInputKey key = efi_tty_get_key();

    while (key.scan_code != SCAN_ESC)
    {
        if (key.unicode_char == CHAR_CARRIAGE_RETURN)
        {
            efi_tty_clear();
            loader_boot(&(LoaderEntry){
                .kernel = str_cast("/kernel.elf"),
            });
        }

        key = efi_tty_get_key();
    }

    efi_st()->runtime_services->reset_system(EFI_RESET_SHUTDOWN, 0, 0, NULL);
}

EFIStatus efi_main(EFIHandle handle, EFISystemTable *st)
{
    efi_init(handle, st);

    st->boot_services->set_watchdog_timer(0, 0, 0, NULL);

    efi_tty_reset();
    efi_tty_clear();

    loader_splash();
    loader_menu();

    assert_unreachable();
}
