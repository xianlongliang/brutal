#include <brutal/text/witty.h>

static char *_witty[] = {
    "Witty comment unavailable :(",

    "...",
    "(Give you up)",
    "[ insert a devse private joke here ]",
    "[ insert a joke here ]",
    "<< Je connais cette théorie >> d0p1",
    "A full kernel panic's what I'm thinking of",
    "Abort, Retry, Fail?",
    "At least it didn't core dump",
    "At least it didn't hang",
    "At least it didn't triple fault",
    "Bad command or file name",
    "But it works on my machine.",
    "Calm down!",
    "Don't do that.",
    "DON'T PANIC!",
    "Error don't exists",
    "Et là c'est le drame...",
    "Everything's going to plan. No, really, that was supposed to happen.",
    "Get the f*** outa my room, I'm playing minecraft",
    "Greenpeace free'd the mallocs \\o/",
    "Hey, wait a minute! What if I type something wrong?",
    "Hi. I'm BRUTAL, and I'm a crashaholic.",
    "Hope. It is the quintessential human delusion",
    "https://www.youtube.com/watch?v=dQw4w9WgXcQ",
    "I blame Cyp.",
    "I blame Monax. ",
    "I have imagined this moment for a long time. Is it real?",
    "I'm not feeling so good...",
    "I'm sorry, Dave.",
    "I'm tired of this ;_;",
    "If you do `make clean` the error will be fixed :tm:",
    "It is remarkable how similar the pattern of programming are to the pattern of insanity.",
    "It just works!",
    "It will be easy they said...",
    "It's copilot fault",
    "It's grub fault",
    "It's loader fault",
    "It's not a good surprise...",
    "Keyboard not found! Please press any key to continue...",
    "Les erreurs au fond, ce n'est qu'une construction social",
    "Let me interject for a moment, what you call errors are in fact brutal/errors",
    "Make it a feature",
    "Minecraft crashed!",
    "My bad.",
    "Never gonna give you up",
    "Never gonna say goodbye",
    "Oh - I know what I did wrong!",
    "On the bright side, I bought you a teddy bear!",
    "One day brutal will be bug free :tm:",
    "OOF!",
    "OoooOOoOoOF!",
    "Oops.",
    "PC LOAD LETTER",
    "Please make it stop",
    "Please report this to the IRC channel",
    "Please try again... This time with less coffee",
    "Please try again... This time with more coffee",
    "Please try again... This time with no coffee",
    "Please try again...",
    "Quite honestly, I wouldn't worry myself about that.",
    "Remember, all I’m offering is the truth. Nothing more.",
    "RIP",
    "skiftOS and WingOS were abandonned for this reason",
    "Surprise! Haha. Well, this is awkward.",
    "Suspicious pointer corrupted the machine.",
    "System consumed all the paper for paging!",
    "The error screen is my worst nightmare",
    "There is a glitch in the matrix",
    "This doesn't make any sense!",
    "This is a feature",
    "Time to put on the blue stripped programming socks",
    "Time to put on the pink stripped programming socks",
    "Time to put on the programming skirt",
    "Time to RIIR!",
    "TIP: when pc = 0 there is a problem",
    "TODO: fix this",
    "Typo in the code.",
    "Uh... Did I do that?",
    "We know the game and we're gonna play it",
    "We'll patch this throught micro-transaction",
    "We've known each other for so long",
    "Welcome to paging hell!",
    "What happened happened and couldn’t have happened any other way.",
    "What if everything was a dream?",
    "What if we kissed during the kernel panic?",
    "You can't fix the core dump, you know",
    "You can't handle the truth!",
    "You don't want to know",
    "You got mail!",
    "You have been warned",
    "You know the rules and so do I",
    "You must construct additional pylons",
    "You need a debugger",
    "You should feel bad",
    "You should go home",
    "You should rewrite it in scheme",
    "You should try to fix it yourself",
    "You should write some documentation",
    "You should write some tests",
    "You're a wizard Harry.",
    "You're not a real hacker",
    "You've been pwned",
    "You've been terminated",
};

Str witty(int seed)
{
    return str$(_witty[seed % array_len$(_witty)]);
}
