#include <gdt.h>

#define AVERION_MASK_16BIT 0xFFFF
#define AVERION_MASK_8BIT 0xFF
#define AVERION_MASK_20BIT 0xFFFFF
#define AVERION_KERNEL_CODE 0x9A
#define AVERION_KERNEL_DATA 0x92
#define AVERION_USER_CODE 0xFA
#define AVERION_USER_DATA 0xF2
#define AVERION_FLAGS 0xC0

static struct gdt_ptr_table gdt_ptr;
static struct gdt_entry_table gdt_entries[5];

/*
1001 - 9
1011 - B
*/

void gdt_flush(uint32_t ptr);

void gdt_init(void)
{
    gdt_ptr.limit = (sizeof(struct gdt_entry_table) * 5) - 1;
    gdt_ptr.base = (uint32_t)(uintptr_t)&gdt_entries[0];

    set_gdt_data(0,0,0,0,0); // null code 
    set_gdt_data(1,0, AVERION_MASK_20BIT, AVERION_KERNEL_CODE, AVERION_FLAGS); // kernel code 
    set_gdt_data(2,0, AVERION_MASK_20BIT, AVERION_KERNEL_DATA, AVERION_FLAGS); // kernel data
    set_gdt_data(3,0, AVERION_MASK_20BIT, AVERION_USER_CODE, AVERION_FLAGS); // user code 
    set_gdt_data(4,0, AVERION_MASK_20BIT, AVERION_USER_DATA, AVERION_FLAGS); // user data

    gdt_flush((uint32_t)(uintptr_t)&gdt_ptr);
}

void set_gdt_data(uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    if (num >= 5) {
        return;
    }
    gdt_entries[num].base_low = (base & AVERION_MASK_16BIT);
    gdt_entries[num].base_middle = (base >> 16) & AVERION_MASK_8BIT;
    gdt_entries[num].base_high = (base >> 24) & AVERION_MASK_8BIT;
    
    gdt_entries[num].limit_low = (limit & AVERION_MASK_16BIT);
    gdt_entries[num].flags = (limit >> 16 & 0xF) | (flags & 0xF0);

    gdt_entries[num].access = access;
}