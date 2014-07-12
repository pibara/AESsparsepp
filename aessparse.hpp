#ifndef _AESSPARSE_HPP
#define _AESSPARSE_HPP
namespace aessparse {
  //Interface for any type of sparse file implementation.
  struct abstract_sparse_file {
      //Low level read and write.
      virtual ssize_t read(void *buf, size_t count, off_t offset) = 0;
      virtual ssize_t write(const void *buf, size_t count, off_t offset) = 0;
      //Navigation functions within hole/data fragments.
      virtual off_t lseek_data(off_t offset) = 0;
      virtual off_t lseek_hole(off_t offset) = 0;
      //Query the size of the file.
      virtual off_t getsize() = 0;
  };
  //Non owning open file rw opened loopback implementation for sparse file.
  struct loopback_sparse_file: public abstract_sparse_file {
        loopback_sparse_file(int file);
        ssize_t read(void *buf, size_t count, off_t offset);
        ssize_t write(const void *buf, size_t count, off_t offset);
        off_t lseek_data(off_t offset);
        off_t lseek_hole(off_t offset);
        off_t getsize();
     private:
        int mFile;
  };
  //Interface for aes sparse file.
  struct abstract_aes_sparse_file {
      //low level read and write functions.
      virtual ssize_t read(void *buf, size_t count, off_t offset) = 0;
      virtual ssize_t write(const void *buf, size_t count, off_t offset) = 0;
      //Don't really know a good interface for communicating padding size yet, this is a place holder for something suitable.
      virtual ssize_t getpadlen() = 0;
  };
  struct aes_sparse_file;
  //movable pimpl wrapper.
  struct aes_sparse_file: public abstract_aes_sparse_file {
        //creation function is frind so it can invoke constructor.
        friend aes_sparse_file create_aes_sparse_file(abstract_sparse_file const &, CryptoPP::SecByteBlock);
        //Move constuctor, needed by creator function invocation.
        aes_sparse_file(aes_sparse_file&& other);
        aes_sparse_file& operator=(aes_sparse_file&& other);
        //No coppy allowed
        aes_sparse_file(aes_sparse_file& other) = delete;
        aes_sparse_file& operator=(aes_sparse_file& other) = delete;
        //destructor will destroy 'owned' pImpl if needed.
        ~aes_sparse_file();
        ssize_t read(void *buf, size_t count, off_t offset);
        ssize_t write(const void *buf, size_t count, off_t offset);
        virtual ssize_t getpadlen();
     private:
        //Private constructor to be used by friend creation function
        aes_sparse_file(abstract_sparse_file *impl);
        //Pointer to implementation.
        abstract_aes_sparse_file *pImpl;
  };
  //Function for creating a aes sparse file using a sparse file and a file encryption key.
  aes_sparse_file create_aes_sparse_file(abstract_sparse_file const &, CryptoPP::SecByteBlock);
}
#endif
