/* 
 * File:   Worker1.h
 * Author: saulario
 *
 * Created on 15 de septiembre de 2016, 6:40
 */
#include <boost/log/trivial.hpp>

#include "Csoft.h"

#ifndef MOD1_WORKER1_H
#define MOD1_WORKER1_H

namespace csoft {
    namespace mod1 {

        class Worker1 {
        public:
            Worker1(const csoft::Csoft *);
            Worker1(const Worker1& orig);
            virtual ~Worker1();
            void doIt(void);
        private:
            boost::log::sources::severity_logger<boost::log::trivial::severity_level> lg;

        };
        
    }
}

#endif /* MOD1_WORKER1_H */

