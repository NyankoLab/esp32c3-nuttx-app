/* ROM function interface esp32c3.rom.ld for esp32c3
 *
 *
 * Generated from ./interface-esp32c3.yml md5sum 93b28a9e1fe42d212018eb4336849208
 *
 * Compatible with ROM where ECO version equal or greater to 0.
 *
 * THIS FILE WAS AUTOMATICALLY GENERATED. DO NOT EDIT.
 */

/***************************************
 Group miniz
 ***************************************/

/* Functions */
mz_adler32 = 0x400000c0;
mz_crc32 = 0x400000c4;
mz_free = 0x400000c8;
tdefl_compress = 0x400000cc;
tdefl_compress_buffer = 0x400000d0;
tdefl_compress_mem_to_heap = 0x400000d4;
tdefl_compress_mem_to_mem = 0x400000d8;
tdefl_compress_mem_to_output = 0x400000dc;
tdefl_get_adler32 = 0x400000e0;
tdefl_get_prev_return_status = 0x400000e4;
tdefl_init = 0x400000e8;
tdefl_write_image_to_png_file_in_memory = 0x400000ec;
tdefl_write_image_to_png_file_in_memory_ex = 0x400000f0;
tinfl_decompress = 0x400000f4;
tinfl_decompress_mem_to_callback = 0x400000f8;
tinfl_decompress_mem_to_heap = 0x400000fc;
tinfl_decompress_mem_to_mem = 0x40000100;
