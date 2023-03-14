#include "SocketMsg.h"


//  NoError message
//
const char* NO_SOCKET_ERROR = "Operation completed successfully.";

//  Socket errors
//
const char* ERR_MSG_200 = "The process have not have appropriate privileges.";
const char* ERR_MSG_201 = "The addresses in the specified address family are not supported.";
const char* ERR_MSG_202 = "The per-process descriptor table is full.";
const char* ERR_MSG_203 = "No more file descriptors are available for the system.";
const char* ERR_MSG_204 = "Insufficient resources were available in the system to complete the call.";
const char* ERR_MSG_205 = "The system was unable to allocate kernel memory to increase the process descriptor table.";
const char* ERR_MSG_206 = "The available STREAMS resources were insufficient for the operation to complete.";
const char* ERR_MSG_207 = "The process is attempting to open a raw socket and does not have the superuser privilege.";
const char* ERR_MSG_208 = "The protocol is not supported by the specified address family or the protocol is not supported.";
const char* ERR_MSG_209 = "The socket type is not supported by the protocol.";

//  Bind errors
//
const char* ERR_MSG_210 = "The requested address is protected and the current user does not have permission to access it."
                          "For an AF_UNIX socket, a component of the path prefix is protected and "
                          "you cannot search it, or the requested name requires writing in a "
                          "directory with a mode that denies write permission.";

const char* ERR_MSG_211 = "The specified address is already in use.";
const char* ERR_MSG_212 = "The specified address is not available from the local machine.";
const char* ERR_MSG_213 = "The specified address is invalid for the address family of the specified socket.";
const char* ERR_MSG_214 = "The socket parameter is not valid.";
const char* ERR_MSG_215 = "For an AF_UNIX socket, the address argument is a null pointer.";
const char* ERR_MSG_216 = "The address parameter is not in a readable part of the user address space.";

const char* ERR_MSG_217 = "The socket is already bound to an address and the protocol does not support binding to a new address; "
                          "the socket has been shut down; or the length or the address_len argument is invalid for the address family.";

const char* ERR_MSG_218 = "For an AF_UNIX socket, an I/O error occurred.";
const char* ERR_MSG_219 = "The socket is already connected.";
const char* ERR_MSG_220 = "The address argument is a null pointer.";
const char* ERR_MSG_221 = "For an AF_UNIX socket, too many symbolic links were encountered in translating the pathname in address.";
const char* ERR_MSG_222 = "A component of the pathname exceeded NAME_MAX characters, or an entire pathname exceeded PATH_MAX characters.";
const char* ERR_MSG_223 = "Insufficient resources were available in the system to complete the call.";
const char* ERR_MSG_224 = "For an AF_UNIX socket, a component of the pathname does not name an existing file or the pathname is an empty string.";
const char* ERR_MSG_225 = "The available STREAMS resources were insufficient for the operation to complete.";
const char* ERR_MSG_226 = "For an AF_UNIX socket, a component of the path prefix of the pathname in address is not a directory.";
const char* ERR_MSG_227 = "The socket parameter refers to a file, not a socket.";
const char* ERR_MSG_228 = "The socket type of the specified socket does not support binding to an address.";
const char* ERR_MSG_229 = "For an AF_UNIX socket, the name would reside on a read-only filesystem.";

//  Listen errors
//
const char* ERR_MSG_230 = "The requested address is protected and the current process does not have permission to access it.";
const char* ERR_MSG_231 = "The socket parameter is not valid.";
const char* ERR_MSG_232 = "The socket is not bound to a local address, and the protocol does not support listening on an unbound socket.";
const char* ERR_MSG_233 = "The socket is already connected; or the socket is shut down.";
const char* ERR_MSG_234 = "Insufficient resources are available in the system to complete the call.";
const char* ERR_MSG_235 = "The socket parameter refers to a file, not a socket.";
const char* ERR_MSG_236 = "The referenced socket is not a type that supports the listen() function.";

//  Accept errors
//
const char* ERR_MSG_237 = "The socket parameter is not valid.";
const char* ERR_MSG_238 = "A connection has been aborted.";
const char* ERR_MSG_239 = "The address parameter or address_len parameter is inaccessible or cannot be written.";
const char* ERR_MSG_240 = "The accept() function was interrupted by a signal that was caught before a valid connection arrived.";
const char* ERR_MSG_241 = "The socket is not accepting connections.";
const char* ERR_MSG_242 = "There are too many open file descriptors.";
const char* ERR_MSG_243 = "The maximum number of file descriptors in the system are already open.";
const char* ERR_MSG_244 = "Insufficient resources are available in the system to complete the call.";
const char* ERR_MSG_245 = "The system was unable to allocate kernel memory to increase the process descriptor table.";
const char* ERR_MSG_246 = "The available STREAMS resources were insufficient for the operation to complete.";
const char* ERR_MSG_247 = "The socket parameter refers to a file, not a socket.";
const char* ERR_MSG_248 = "The referenced socket cannot accept connections.";
const char* ERR_MSG_249 = "A protocol error occurred.";
const char* ERR_MSG_250 = "The socket is marked nonblocking, and no connections are present to be accepted.";

//  GetHostByName errors
//
const char* ERR_MSG_251 = "Host is unknown.";
const char* ERR_MSG_252 = "The server recognized the request and the name, but no address is available for the name.  Another type of name server request may be successful.";
const char* ERR_MSG_253 = "An unexpected server failure occurred.  This is a nonrecoverable error.";
const char* ERR_MSG_254 = "A transient error occurred, for example, the server did not respond. A retry at some later time may be successful.";
const char* ERR_MSG_255 = "The name, hptr, or hdptr is invalid.";

//  Connect errors
//
const char* ERR_MSG_257 = "Search permission is denied for a component of the path prefix; orwrite access to the named socket is denied.";
const char* ERR_MSG_258 = "The specified address is already in use.";
const char* ERR_MSG_259 = "The specified address is not available from the local machine.";
const char* ERR_MSG_260 = "The addresses in the specified address family cannot be used with this socket.";
const char* ERR_MSG_261 = "A connection request is already in progress for the specified socket.";
const char* ERR_MSG_262 = "The socket parameter is not valid.";
const char* ERR_MSG_263 = "The attempt to connect was rejected.";
const char* ERR_MSG_264 = "The remote host reset the connection request.";
const char* ERR_MSG_265 = "The address parameter is not in a readable part of the user address space.";
const char* ERR_MSG_266 = "The specified host is not reachable.";
const char* ERR_MSG_267 = "O_NONBLOCK is set for the file descriptor for the socket and the connection cannot be immediately established; the connection will be established asynchronously.";
const char* ERR_MSG_268 = "The connect() function was interrupted by a signal while waiting for the connection to be established. The connection establishment may continue asynchronously.";
const char* ERR_MSG_269 = "The value of the address_len parameter is invalid for the specified address family; or the sa_family field in the socket address structure is invalid for the protocol.";
const char* ERR_MSG_270 = "For an AF_UNIX socket, an I/O error occurred while reading from or writing to the file system.";
const char* ERR_MSG_271 = "The socket is already connected.";
const char* ERR_MSG_272 = "For an AF_UNIX socket, too many symbolic links were encountered in translating the pathname in address.";
const char* ERR_MSG_273 = "A component of the pathname exceeded NAME_MAX characters, or an entire pathname exceeded PATH_MAX characters.";
const char* ERR_MSG_274 = "The local network connection is not operational.";
const char* ERR_MSG_275 = "No route to the network or host is present.";
const char* ERR_MSG_276 = "Insufficient resources are available in the system to complete the call.";
const char* ERR_MSG_277 = "For an AF_UNIX socket, a component of the pathname does not name an existing file or the pathname is an empty string.";
const char* ERR_MSG_278 = "The available STREAMS resources were insufficient for the operation to complete.";
const char* ERR_MSG_279 = "For an AF_UNIX socket, a component of the path prefix of the pathname in address is not a directory.";
const char* ERR_MSG_280 = "The socket parameter refers to a file, not a socket.";
const char* ERR_MSG_281 = "The socket is listening and cannot be connected.";
const char* ERR_MSG_282 = "The specified address has a different type than the socket bound to the specified peer address.";
const char* ERR_MSG_283 = "The establishment of a connection timed out before a connection was made.";
const char* ERR_MSG_284 = "The socket is marked nonblocking, so the connection cannot be immediately completed.  The application program can select the socket for writing during the connection process.";

//  Receive errors
//
const char* ERR_MSG_285 = "The read() would cause the information label of the process to float to an information level that is not dominated by the process's sensitivity level.";
const char* ERR_MSG_286 = "The socket parameter is not valid.";
const char* ERR_MSG_287 = "A connection was forcibly closed by a peer.";

const char* ERR_MSG_288 = "The data was directed to be received into a nonexistent or protected part of the process "
                          "address space. The buffer parameter is invalid.";

const char* ERR_MSG_289 = "A signal interrupted the recv() function before any data was available.";
const char* ERR_MSG_290 = "The MSG_OOB option is set and no out-of-band data is available.";
const char* ERR_MSG_291 = "An I/O error occurred while reading from or writing to the file system.";
const char* ERR_MSG_292 = "Insufficient resources were available in the system to complete the call.";
const char* ERR_MSG_293 = "The system did not have sufficient memory to fulfill the request.";
const char* ERR_MSG_294 = "The available STREAMS resources were insufficient for the operation to complete.";
const char* ERR_MSG_295 = "Receive is attempted on a connection-oriented socket that is not connected.";
const char* ERR_MSG_296 = "The socket parameter refers to a file, not a socket.";
const char* ERR_MSG_297 = "The specified options are not supported for this socket type or protocol.";

const char* ERR_MSG_298 = "The connection timed out during connection establishment or due to a transmission timeout "
                          "on active connection.";

const char* ERR_MSG_299 = "The socket is marked nonblocking, and no data is waiting to be received.";
const char* ERR_MSG_300 = "The socket is not connection-oriented and no peer address is set.";
const char* ERR_MSG_301 = "The message is too large to be sent all at once, as the socket requires.";
const char* ERR_MSG_302 = "The local network connection is not operational.";
const char* ERR_MSG_303 = "The destination network is unreachable.";

const char* ERR_MSG_304 = "The socket is shut down for writing, or the socket is connection-oriented and the peer is "
                          "closed or shut down for reading. In the latter case, and if the socket is of type SOCK_STREAM, the "
                          "SIGPIPE signal is generated to the calling process.";

