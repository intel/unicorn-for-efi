#include <uc_priv.h>
#include "qemu/osdep.h"

void qemu_anon_ram_free(struct uc_struct *uc, void *ptr, size_t size)
{
  FreePages (ptr, EFI_SIZE_TO_PAGES (size));
}

void *qemu_anon_ram_alloc(struct uc_struct *uc, size_t size, uint64_t *align)
{
  void *ptr;

  ptr = AllocatePages (EFI_SIZE_TO_PAGES (size));
  if (ptr == NULL) {
    return ptr;
  }

  *align = EFI_PAGE_SIZE;
  return ptr;
}

void qemu_vfree(void *ptr)
{
  free(ptr);
}

void *qemu_memalign(size_t alignment, size_t size)
{
  return memalign(alignment, size);
}
