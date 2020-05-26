9200 // Boot loader.
9201 //
9202 // Part of the boot block, along with bootasm.S, which calls bootmain().
9203 // bootasm.S has put the processor into protected 32-bit mode.
9204 // bootmain() loads an ELF kernel image from the disk starting at
9205 // sector 1 and then jumps to the kernel entry routine.
9206 
9207 #include "types.h"
9208 #include "elf.h"
9209 #include "x86.h"
9210 #include "memlayout.h"
9211 
9212 #define SECTSIZE  512
9213 
9214 void readseg(uchar*, uint, uint);
9215 
9216 void
9217 bootmain(void)
9218 {
9219   struct elfhdr *elf;
9220   struct proghdr *ph, *eph;
9221   void (*entry)(void);
9222   uchar* pa;
9223 
9224   elf = (struct elfhdr*)0x10000;  // scratch space
9225 
9226   // Read 1st page off disk
9227   readseg((uchar*)elf, 4096, 0);
9228 
9229   // Is this an ELF executable?
9230   if(elf->magic != ELF_MAGIC)
9231     return;  // let bootasm.S handle error
9232 //load code from elf to memory
9233   // Load each program segment (ignores ph flags).
9234   ph = (struct proghdr*)((uchar*)elf + elf->phoff);
9235   eph = ph + elf->phnum;
9236 //Abhijit: number of program headers
9237   for(; ph < eph; ph++){
9238 //Abhijit: iterate over each program header
9239     pa = (uchar*)ph->paddr;
9240 //Abhijit:the physical address to load program
9241 //Abhijit: read ph->filesz bytes into 'pa' from ph->off in kernel/disk
9242     readseg(pa, ph->filesz, ph->off);
9243     if(ph->memsz > ph->filesz)
9244       stosb(pa + ph->filesz, 0, ph->memsz - ph->filesz);
9245   }
9246 
9247 
9248 
9249 
9250   // Call the entry point from the ELF header.
9251   // Does not return!
9252 //Abhijit: elf-> entry was set by linker using kernel.id
9253 //this is address 0x80100000 specified in kernel.id
9254 //see kernel.asm for kernel assembly code
9255   entry = (void(*)(void))(elf->entry);
9256   entry();
9257 }
9258 
9259 void
9260 waitdisk(void)
9261 {
9262   // Wait for disk ready.
9263   while((inb(0x1F7) & 0xC0) != 0x40)
9264     ;
9265 }
9266 
9267 // Read a single sector at offset into dst.
9268 void
9269 readsect(void *dst, uint offset)
9270 {
9271   // Issue command.
9272   waitdisk();
9273   outb(0x1F2, 1);   // count = 1
9274   outb(0x1F3, offset);
9275   outb(0x1F4, offset >> 8);
9276   outb(0x1F5, offset >> 16);
9277   outb(0x1F6, (offset >> 24) | 0xE0);
9278   outb(0x1F7, 0x20);  // cmd 0x20 - read sectors
9279 
9280   // Read data.
9281   waitdisk();
9282   insl(0x1F0, dst, SECTSIZE/4);
9283 }
9284 
9285 // Read 'count' bytes at 'offset' from kernel into physical address 'pa'.
9286 // Might copy more than asked.
9287 void
9288 readseg(uchar* pa, uint count, uint offset)
9289 {
9290   uchar* epa;
9291 
9292   epa = pa + count;
9293 
9294   // Round down to sector boundary.
9295   pa -= offset % SECTSIZE;
9296 
9297   // Translate from bytes to sectors; kernel starts at sector 1.
9298   offset = (offset / SECTSIZE) + 1;
9299 
9300   // If this is too slow, we could read lots of sectors at a time.
9301   // We'd write more to memory than asked, but it doesn't matter --
9302   // we load in increasing order.
9303   for(; pa < epa; pa += SECTSIZE, offset++)
9304     readsect(pa, offset);
9305 }
9306 
9307 
9308 
9309 
9310 
9311 
9312 
9313 
9314 
9315 
9316 
9317 
9318 
9319 
9320 
9321 
9322 
9323 
9324 
9325 
9326 
9327 
9328 
9329 
9330 
9331 
9332 
9333 
9334 
9335 
9336 
9337 
9338 
9339 
9340 
9341 
9342 
9343 
9344 
9345 
9346 
9347 
9348 
9349 
