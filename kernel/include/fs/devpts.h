#ifndef _DEVPTS_H
#define _DEVPTS_H

#include <fs/vfs.h>

extern struct fs devpts;
extern struct inode *devpts_root;
extern struct vnode vdevpts_root;

#endif /* ! _DEVPTS_H */
