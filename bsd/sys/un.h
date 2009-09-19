/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)un.h	8.3 (Berkeley) 2/19/95
 */

#ifndef _SYS_UN_H_
#define _SYS_UN_H_

#include <sys/appleapiopts.h>
#include <sys/cdefs.h>
#include <sys/_types.h>

/* [XSI] The sa_family_t type shall be defined as described in <sys/socket.h> */
#ifndef _SA_FAMILY_T
#define _SA_FAMILY_T
typedef __uint8_t		sa_family_t;
#endif

/*
 * [XSI] Definitions for UNIX IPC domain.
 */
struct	sockaddr_un {
	unsigned char	sun_len;	/* sockaddr len including null */
	sa_family_t	sun_family;	/* [XSI] AF_UNIX */
	char		sun_path[104];	/* [XSI] path name (gag) */
};

#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
/* Socket options. */
#define LOCAL_PEERCRED          0x001           /* retrieve peer credentails */
#endif	/* (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE) */


#ifdef KERNEL
#ifdef PRIVATE
#include <kern/locks.h>
__BEGIN_DECLS
struct mbuf;
struct socket;
struct sockopt;

int	uipc_usrreq(struct socket *so, int req, struct mbuf *m,
		struct mbuf *nam, struct mbuf *control);
int	uipc_ctloutput (struct socket *so, struct sockopt *sopt);
int	unp_connect2(struct socket *so, struct socket *so2);
void	unp_dispose(struct mbuf *m);
int	unp_externalize(struct mbuf *rights);
void	unp_init(void) __attribute__((section("__TEXT, initcode")));
extern	struct pr_usrreqs uipc_usrreqs;
int     unp_lock(struct socket *, int, void *);
int     unp_unlock(struct socket *, int, void *);
lck_mtx_t* unp_getlock(struct socket *, int);
__END_DECLS
#endif /* PRIVATE */
#else /* !KERNEL */

#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
/* actual length of an initialized sockaddr_un */
#define SUN_LEN(su) \
	(sizeof(*(su)) - sizeof((su)->sun_path) + strlen((su)->sun_path))
#endif	/* (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE) */

#endif /* KERNEL */

#endif /* !_SYS_UN_H_ */