/*
 * Microwindows keyboard driver for Compaq iPAQ
 *
 * Copyright (c) 2000, 2003 Century Software Embedded Technologies
 * Written by Jordan Crouse
 */
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "kbd_types.h"
#include "keyboard.h"


#define KEYBOARD "/dev/mcu/kbd"

static int fd;

typedef struct{
	MWKEY mwkey;
	int scancode;
}KeyMap;

static MWKEY scancodes[64];
static KeyMap keymap[] = {
      {MWKEY_KP0,  0x1d}, 
      {MWKEY_KP1,  0x21}, 
      {MWKEY_KP2,  0x25}, 
      {MWKEY_KP3,  0x23}, 
      {MWKEY_KP4,  0x29}, 
      {MWKEY_KP5,  0x2d}, 
      {MWKEY_KP6,  0x2b}, 
      {MWKEY_KP7,  0x31}, 
      {MWKEY_KP8,  0x35}, 
      {MWKEY_KP9,  0x33}, 
      {MWKEY_NUMLOCK, 	0x11}, 
      {MWKEY_KP_DIVIDE,	0x15}, 
      {MWKEY_KP_MULTIPLY,	0x13}, 
      {MWKEY_KP_MINUS,	0x0b}, 
      {MWKEY_KP_PLUS,		0x34}, 
      {MWKEY_KP_ENTER,	0x24}, 
      {MWKEY_KP_DEL,	0x1b}, 
};


int
KBD_Open(void)
{
	int i;

	/* Open the keyboard and get it ready for use */
	fd = open(KEYBOARD, O_RDONLY | O_NONBLOCK);

	if (fd < 0) {
		printf("%s - Can't open keyboard!\n", __FUNCTION__);
		return -1;
	}

	for (i=0; i<sizeof(scancodes)/sizeof(scancodes[0]); i++)
		scancodes[i]=MWKEY_UNKNOWN;

	for (i=0; i< sizeof(keymap)/sizeof(keymap[0]); i++)
		scancodes[keymap[i].scancode]=keymap[i].mwkey;

	return fd;
}


void
KBD_Close(void)
{
	close(fd);
	fd = -1;
}

void
KBD_GetModifierInfo(MWKEYMOD * modifiers, MWKEYMOD * curmodifiers)
{
	if (modifiers)
		*modifiers = 0;	/* no modifiers available */
	if (curmodifiers)
		*curmodifiers = 0;
}


int
KBD_Read(char* kbuf, MWKEYMOD * modifiers, MWSCANCODE * scancode)
{
	int keydown = 0;
	int cc = 0;
	char buf,key;

	cc = read(fd, &buf, 1);

	if (cc < 0) {
		if ((errno != EINTR) && (errno != EAGAIN)
		    && (errno != EINVAL)) {
			perror("KBD KEY");
			return (-1);
		} else {
			return (0);
		}
	}
	if (cc == 0)
		return (0);

	/* If the code is big than 127, then we know that */
	/* we have a key down.  Figure out what we've got */

	*modifiers = 0;

	if (buf & 0x80) {
		keydown = 1;	/* Key pressed but not released */
	} else {
		keydown = 2;	/* key released */
	}

	buf &= (~0x80);
	if( buf >= sizeof(scancodes) ) *kbuf = MWKEY_UNKNOWN;
	*scancode = scancodes[(int) buf];
	*kbuf = *scancode ;
//	printf("%c",*kbuf);  	
//	printf("by threewater: orgvalue=%x key=%c %x keystatus=%d, scancode=%x\n",buf, *kbuf,*kbuf,keydown, *scancode);
	return keydown;
	
}
