#include <stdio.h>
#include <sys/time.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#include <common/cycles.h>
#include <common/dump_utils.h>

#include "nvme_device.h"
#include "tests.h"


void basic_block_read(NVME_device * dev, size_t num_blocks) {

  PLOG("running basic_block_read..");
  const unsigned qid = 1;
  assert(num_blocks < 256);

  Notify_object nobj;

  /* set up call back */
  dev->io_queue(qid)->callback_manager()->register_callback(qid,
                                                            &Notify_object::notify_callback,
                                                            (void*)&nobj);

  addr_t phys = 0;
  void * p = dev->alloc_dma_pages(1,&phys);

  assert(p);
  assert(phys);

  uint16_t cid;
  for(unsigned i=0;i<num_blocks;i++) {

    cid = dev->block_async_read(qid,
                                phys,
                                i, /* LBA */
                                1); /* num blocks */
    
    PLOG("Block read cid=%u",cid);
    
    hexdump(p,512);
  }
  nobj.set_when(cid);
  nobj.wait();
  PLOG("expected block reads complete.");

  dev->free_dma_pages(p);
}


void basic_block_write(NVME_device * dev, size_t num_blocks) {

  PLOG("running basic_block_write..");
  //  Exokernel::Memory::huge_system_configure_nrpages(10);
  const unsigned qid = 1;
  Notify_object nobj;

  /* set up call back */
  dev->io_queue(qid)->callback_manager()->register_callback(qid,
                                                            &Notify_object::notify_callback,
                                                            (void*)&nobj);

  unsigned num_data_pages = 4;
  unsigned num_data_blocks = (PAGE_SIZE * num_data_pages) / 512;

  PLOG("Allocated %d pages, %d blocks",num_data_pages, num_data_blocks);

  addr_t phys = 0;
  //  void * p = Exokernel::Memory::alloc_pages(num_data_pages,&phys);
  void * p = dev->alloc_dma_pages(num_data_pages,&phys);
  memset(p,0xfe,num_data_pages*PAGE_SIZE);
  assert(p);
  assert(phys);

  char * q = (char *) p;
  for(unsigned i=0;i<num_data_blocks;i++) {
    /* write a value in */
    memset(q,i+1,512);
    q+=512;
  }

  uint16_t cid;
  //  for(unsigned i=0;i<num_blocks;i++) {
  for(unsigned i=0;i<1;i++) {

    cid = dev->block_async_write(qid,
                                 phys+((i+8)*512), //phys+((i%num_data_blocks)*512),
                                 i, /* LBA */
                                 1);/* num blocks */
    
    PLOG("*** Block written cid=%u",cid);
  }

  nobj.set_when(cid);
  nobj.wait();
  PLOG("******** Blocks written!!!");

  dev->free_dma_pages(p);
}
