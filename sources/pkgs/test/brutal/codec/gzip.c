#include <brutal/alloc/global.h>
#include <brutal/codec/gzip/gzip.h>
#include "test/test.h"

TEST(gzip_empty_raw)
{
    uint8_t out_storage[512];
    // Empty buffer, uncompressed
    const uint8_t in_storage[] = {
        0x1F, 0x8B, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0B,
        0x01, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00};

    size_t size = UNWRAP(gzip_decompress_data(in_storage, sizeof(in_storage), out_storage, sizeof(out_storage)));

    assert_equal(size, 0u);
}

TEST(gzip_empty_fixed)
{
    uint8_t out_storage[512];
    // Empty buffer, fixed Huffman
    const uint8_t in_storage[] = {
        0x1F, 0x8B, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0B,
        0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    size_t size = UNWRAP(gzip_decompress_data(in_storage, sizeof(in_storage), out_storage, sizeof(out_storage)));

    assert_equal(size, 0u);
}

TEST(gzip_empty_dynamic)
{
    uint8_t out_storage[512];
    // Empty buffer, dynamic Huffman
    const uint8_t in_storage[] = {
        0x1F, 0x8B, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0B,
        0x05, 0xC1, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xFF,
        0xD5, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    size_t size = UNWRAP(gzip_decompress_data(in_storage, sizeof(in_storage), out_storage, sizeof(out_storage)));

    assert_equal(size, 0u);
}

TEST(gzip_onebyte_raw)
{
    uint8_t out_storage[512];
    // One byte 00, uncompressed
    const uint8_t in_storage[] = {
        0x1F, 0x8B, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0B,
        0x01, 0x01, 0x00, 0xFE, 0xFF, 0x00, 0x8D, 0xEF, 0x02, 0xD2,
        0x01, 0x00, 0x00, 0x00};

    size_t size = UNWRAP(gzip_decompress_data(in_storage, sizeof(in_storage), out_storage, sizeof(out_storage)));

    assert_equal(size, 1u);
    assert_equal(out_storage[0], 0u);
}

TEST(gzip_onebyte_fixed)
{
    uint8_t out_storage[512];
    // One byte 00, fixed Huffman
    const uint8_t in_storage[] = {
        0x1F, 0x8B, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0B,
        0x63, 0x00, 0x00, 0x8D, 0xEF, 0x02, 0xD2, 0x01, 0x00, 0x00,
        0x00};

    size_t size = UNWRAP(gzip_decompress_data(in_storage, sizeof(in_storage), out_storage, sizeof(out_storage)));

    assert_equal(size, 1u);
    assert_equal(out_storage[0], 0u);
}

TEST(gzip_onebyte_dynamic)
{
    uint8_t out_storage[512];
    // One byte 00, dynamic Huffman
    const uint8_t in_storage[] = {
        0x1F, 0x8B, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0B,
        0x05, 0xC1, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xFF,
        0xD5, 0x10, 0x8D, 0xEF, 0x02, 0xD2, 0x01, 0x00, 0x00, 0x00};

    size_t size = UNWRAP(gzip_decompress_data(in_storage, sizeof(in_storage), out_storage, sizeof(out_storage)));

    assert_equal(size, 1u);
    assert_equal(out_storage[0], 0u);
}

TEST(gzip_fhcrc)
{
    uint8_t out_storage[512];
    // One byte 00, uncompressed, fhcrc
    const uint8_t in_storage[] = {
        0x1F, 0x8B, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0B,
        0x17, 0x9D, 0x01, 0x01, 0x00, 0xFE, 0xFF, 0x00, 0x8D, 0xEF,
        0x02, 0xD2, 0x01, 0x00, 0x00, 0x00};

    size_t size = UNWRAP(gzip_decompress_data(in_storage, sizeof(in_storage), out_storage, sizeof(out_storage)));

    assert_equal(size, 1u);
    assert_equal(out_storage[0], 0u);
}

TEST(gzip_fextra)
{
    uint8_t out_storage[512];
    // One byte 00, uncompressed, fextra
    const uint8_t in_storage[] = {
        0x1F, 0x8B, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0B,
        0x04, 0x00, 0x64, 0x61, 0x74, 0x61, 0x01, 0x01, 0x00, 0xFE,
        0xFF, 0x00, 0x8D, 0xEF, 0x02, 0xD2, 0x01, 0x00, 0x00, 0x00};

    size_t size = UNWRAP(gzip_decompress_data(in_storage, sizeof(in_storage), out_storage, sizeof(out_storage)));

    assert_equal(size, 1u);
    assert_equal(out_storage[0], 0u);
}

TEST(gzip_fname)
{
    uint8_t out_storage[512];
    // One byte 00, uncompressed, fname
    const uint8_t in_storage[] = {
        0x1F, 0x8B, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0B,
        0x66, 0x6F, 0x6F, 0x2E, 0x63, 0x00, 0x01, 0x01, 0x00, 0xFE,
        0xFF, 0x00, 0x8D, 0xEF, 0x02, 0xD2, 0x01, 0x00, 0x00, 0x00};

    size_t size = UNWRAP(gzip_decompress_data(in_storage, sizeof(in_storage), out_storage, sizeof(out_storage)));

    assert_equal(size, 1u);
    assert_equal(out_storage[0], 0u);
}

TEST(gzip_fcomment)
{
    uint8_t out_storage[512];
    // One byte 00, uncompressed, fcomment
    const uint8_t in_storage[] = {
        0x1F, 0x8B, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0B,
        0x68, 0x65, 0x6C, 0x6C, 0x6F, 0x00, 0x01, 0x01, 0x00, 0xFE,
        0xFF, 0x00, 0x8D, 0xEF, 0x02, 0xD2, 0x01, 0x00, 0x00, 0x00};

    size_t size = UNWRAP(gzip_decompress_data(in_storage, sizeof(in_storage), out_storage, sizeof(out_storage)));

    assert_equal(size, 1u);
    assert_equal(out_storage[0], 0u);
}
