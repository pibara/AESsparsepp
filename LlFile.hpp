struct LlFile {
    int mFd;
  public:
    LlFile(const char *pathname, int flags);
    LlFile(const char *pathname, int flags, mode_t mode);
    ~LlFile();
    ssize_t pread(void *buf, size_t count, off_t offset);
    ssize_t pwrite(const void *buf, size_t count, off_t offset);
};
