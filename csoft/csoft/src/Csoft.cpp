/* 
 * File:   Csoft.cpp
 * Author: saulario
 * 
 * Created on 15 de septiembre de 2016, 6:52
 */
#include <thread>

#include "Csoft.h"
#include "mod1/Worker1.h"
#include "mod2/Worker2.h"

using namespace csoft;

Csoft::Csoft() {
}

Csoft::Csoft(const Csoft& orig) {
}

Csoft::~Csoft() {
}

void lanzar(int job) {

    //    switch(job) {
    //        case 1:
    //            mod1::Worker1 w(csoft);
    //            w.doIt();
    //            break;
    //        case 2:
    //            mod2::Worker2 w2(csoft);
    //            w2.doIt();
    //            break;
    //    }

}

int Csoft::doIt(int argc, char **argv) {
    BOOST_LOG_SEV(lg, boost::log::trivial::info) << "-----> Begin";

    std::thread t1(Csoft::launch, this, 1);
    std::thread t2(Csoft::launch, this, 2);

    t1.join();
    t2.join();

    BOOST_LOG_SEV(lg, boost::log::trivial::info) << "<----- End";
}

void Csoft::launch(const Csoft * csoft, unsigned int i) {
    switch (i) {
        case 1:
        {
            mod1::Worker1 w1(csoft);
            w1.doIt();
        }
            break;
        case 2:
        {
            mod2::Worker2 w2(csoft);
            w2.doIt();
        }
            break;
    }
}

//static void Csoft::launch(Csoft & csoft, int job) {
//    
//    switch(job) {
//        case 1:
//            mod1::Worker1 w(csoft);
//            w.doIt();
//            break;
//        case 2:
//            mod2::Worker2 w(csoft);
//            w.doIt();
//            break;
//    }
//    
//}

