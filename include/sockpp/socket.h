#ifndef __sockpp_socket_h
#define __sockpp_socket_h


namespace sockpp {
    class socket_initializer {
    private:
        socket_initializer();

        socket_initializer(const socket_initializer &) = delete;

        socket_initializer &operator=(const socket_initializer &) = delete;

        friend class socket;

    public:
        static void initialize() {
            static socket_initializer sock_init;
        }

        ~socket_initializer();
    };

    void initialize();
}


#endif  // __sockpp_socket_h
