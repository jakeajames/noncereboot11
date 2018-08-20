#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "kutils.h"
#include "finder.h"
#include "offsets.h"
#include "debug.h"

uint64_t task_self_addr() {
    
    uint64_t selfproc = proc_for_pid(getpid());
    if (selfproc == 0) {
        fprintf(stderr, "failed to find our task addr\n");
        exit(-1);
    }
    uint64_t addr = rk64(selfproc + OFF_TASK);
    
    uint64_t task_addr = addr;
    uint64_t itk_space = rk64(task_addr + OFF_TASK__ITK_SPACE);
    
    uint64_t is_table = rk64(itk_space + OFF_IPC_SPACE__IS_TABLE);
    
    uint32_t port_index = mach_task_self() >> 8;
    const int sizeof_ipc_entry_t = 0x18;
    
    uint64_t port_addr = rk64(is_table + (port_index * sizeof_ipc_entry_t));
    
    return port_addr;
}


// from Ian Beer's find_port.c
uint64_t find_port_address(mach_port_name_t port) {
    uint64_t task_port_addr = task_self_addr();

    uint64_t task_addr = rk64(task_port_addr + OFF_IPC_PORT__IP_KOBJECT);
    uint64_t itk_space = rk64(task_addr + OFF_TASK__ITK_SPACE);
    uint64_t is_table = rk64(itk_space + OFF_IPC_SPACE__IS_TABLE);

    uint32_t port_index = port >> 8;
    uint64_t port_addr = rk64(is_table + (port_index * SIZ_IPC_ENTRY_T));
    return port_addr;
}
