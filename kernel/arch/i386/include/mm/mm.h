#ifndef _I386_MM_H
#define _I386_MM_H

#include <core/system.h>
#include <cpu/cpu.h>

#define NR_PAGE_SIZE           2
#define KERNEL_HEAP_SIZE       (8ULL * 1024 * 1024)  /* 8 MiB */

#if ARCH_BITS==32
#define ARCH_KVMEM_BASE        (0xD0000000UL)
#define ARCH_KVMEM_NODES_SIZE  (0x00100000UL)
#else
#define ARCH_KVMEM_BASE        (0xFFFFD00000000000ULL)
#define ARCH_KVMEM_NODES_SIZE  (0x00100000ULL)
#endif

extern char _VMA; /* Must be defined in linker script */
#define VMA(obj)  ((typeof((obj)))((uintptr_t)(void*)&_VMA + (uintptr_t)(void*)(obj)))
#define LMA(obj)  ((typeof((obj)))((uintptr_t)(void*)(obj)) - (uintptr_t)(void*)&_VMA)

static inline void tlb_flush(void)
{
    write_cr3(read_cr3());
}

#if ARCH_BITS==32
typedef uint32_t paddr_t;
typedef uint32_t vaddr_t;
#else
typedef uint64_t paddr_t;
typedef uint64_t vaddr_t;
#endif

paddr_t arch_get_frame(void);
void arch_release_frame(paddr_t paddr);
//void arch_switch_mapping(paddr_t map);
void arch_mm_fork(paddr_t base, paddr_t fork);
void arch_mm_page_fault(vaddr_t vaddr, int err);

struct pmap {
    uintptr_t map;
    uint32_t refcnt;
};

void arch_pmap_init(void);
struct pmap *arch_pmap_switch(struct pmap *pmap);
struct pmap *arch_pmap_create(void);
void arch_pmap_incref(struct pmap *pmap);
void arch_pmap_decref(struct pmap *pmap);
void arch_pmap_fork(struct pmap *src_map, struct pmap *dst_map);
int  arch_pmap_add(struct pmap *pmap, vaddr_t va, paddr_t pa, uint32_t flags);
void arch_pmap_remove(struct pmap *pmap, vaddr_t sva, vaddr_t eva);

#include_next <mm/mm.h>

#endif /* ! _I386_MM_H */
