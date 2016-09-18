/* 
 * File:   Worker2.h
 * Author: saulario
 *
 * Created on 15 de septiembre de 2016, 6:40
 */
#include <boost/log/trivial.hpp>

#include "Csoft.h"

#ifndef MOD2_WORKER2_H
#define MOD2_WORKER2_H

namespace csoft {
    namespace mod2 {

        class Worker2 {
        public:
            Worker2(const csoft::Csoft *);
            Worker2(const Worker2& orig);
            virtual ~Worker2();
            void doIt(void);
        private:
            boost::log::sources::severity_logger<boost::log::trivial::severity_level> lg;

        };
        
    }
}

#endif /* MOD2_WORKER2_H */

