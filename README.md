AESsparse++
===========

C++ library for creating and accessing sparse AES encrypted files.

This library is break-off project of the former MinorFS2 project. 
The library aims to be a low level library that allows AES encrypted files
to live on a sparse-file supporting file-system, without ignoring the 
sparse-file support. That is, other than in many solutions, holes in the 
unencrypted data will be stored as holes in the encrypted file. 


