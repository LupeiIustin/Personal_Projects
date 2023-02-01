#include <list>
#include "util/RuntimeThread.h"
#include "util/Socket.h"
#define PORT 22520

int main(){

    Socket s;
    s.open();
    s.bind(PORT);
    s.listen(100);

    while(true) {
        try {
            Socket c = s.accept();

            auto * thread = new RuntimeThread(c, 0);
            RuntimeThread::add_thread(thread);
            RuntimeThread::create_thread(thread, RuntimeThread::init_thread);
        } catch (std :: exception const &) {
            continue;
        }
//        RuntimeThread::remove_thread(thread);
    }

    s.close();
    return 0;
}
