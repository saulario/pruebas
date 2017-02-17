#ifndef MESSAGETYPES_H
#define MESSAGETYPES_H

#include<vector>

#include "SegmentTypes.h"

namespace iot {
    namespace messaging {

        class Message {
        public:
            Message();
            Message(const char *);
            Message(const std::string &);

            void fromString(const std::string &);
            std::string toString(void);

        private:
            std::unique_ptr<BMSegment> bm;
            std::unique_ptr<FRSegment> fr;

            std::unique_ptr<std::vector<std::unique_ptr<GPSegment>>> gps;
            std::unique_ptr<std::vector<std::unique_ptr<TPSegment>>> tps;

            std::unique_ptr<EMSegment> em;


            std::unique_ptr<std::string> raw;


        };

    }
}

#endif /* MESSAGETYPES_H */

