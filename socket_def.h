#pragma once

#ifdef _WINDOWS

#define socket_t SOCKET
#define socket_close closesocket

#else

#define socket_t int	
#define socket_close close

#endif