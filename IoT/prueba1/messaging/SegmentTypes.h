#ifndef SEGMENTTYPES_H
#define SEGMENTTYPES_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace iot {
    namespace messaging {
        
        class BMSegment {
        public:
            std::string identifier;
            boost::posix_time::ptime creationDate;
            std::string version;
            std::string revision;

            void fromString(const std::string &);
            
        private:
        };
        
        class FRSegment {
        public:
            std::string deviceId;
            
            void fromString(const std::string &);
        private:
        };
        
        class GPSegment {
        public:
            std::string sensorId;
            double latitude;
            double longitude;
            double altitude;
            double bearing;
            double speed;
            unsigned int satellites;
            boost::posix_time::ptime gpsTime;
            
            void fromString(const std::string &);
        };
        
        class TPSegment {
        public:
            std::string sensorId;
            double temp1;
            std::unique_ptr<double> temp2;
            std::unique_ptr<double> temp3;
            
            void fromString(const std::string &);
        };
        
        struct EMSegment {
        public:
            std::string identifier;
            unsigned int records;
        private:
        };
        
    }
}

#endif /* SEGMENTTYPES_H */

