#ifndef VWZE_ENTITY_H
#define VWZE_ENTITY_H
#include <tntdb/blob.h>
#include <tntdb/date.h>
#include <tntdb/datetime.h>
#include <tntdb/time.h>
namespace vwze {
    namespace entity {

        struct Doc {
        public:
            long doccod; /*  */
            std::string docrel; /*  */
            std::string docexp; /*  */
            tntdb::Date docfec; /*  */
            std::string docorgzon; /*  */
            std::string docorgpob; /*  */
            std::string docdeszon; /*  */
            std::string docdespob; /*  */
            std::string docflu; /*  */
            std::string docfab; /*  */
            std::string docdun; /*  */
            std::string docpro; /*  */
            double docpes; /*  */
            double docvol; /*  */
            double docpef; /*  */
            Doc();
            ~Doc();
            bool operator==(const Doc &);
        private:
        };

        struct Dod {
        public:
            long dodcod; /*  */
            std::string dodrel; /*  */
            std::string dodexp; /*  */
            tntdb::Date dodfec; /*  */
            std::string dodorgzon; /*  */
            std::string dodorgpob; /*  */
            std::string doddeszon; /*  */
            std::string doddespob; /*  */
            std::string dodflu; /*  */
            std::string dodfab; /*  */
            std::string doddun; /*  */
            std::string dodpro; /*  */
            double dodpes; /*  */
            double dodvol; /*  */
            double dodpef; /*  */
            Dod();
            ~Dod();
            bool operator==(const Dod &);
        private:
        };

        struct Pro {
        public:
            std::string produn; /*  */
            std::string proraz; /*  */
            Pro();
            ~Pro();
            bool operator==(const Pro &);
        private:
        };

        struct Zon {
        public:
            std::string zoncod; /*  */
            std::string zondes; /*  */
            double zonman; /*  */
            Zon();
            ~Zon();
            bool operator==(const Zon &);
        private:
        };

        struct Zoo {
        public:
            long zoocod; /*  */
            std::string zoozoncod; /*  */
            std::string zoopcp; /*  */
            Zoo();
            ~Zoo();
            bool operator==(const Zoo &);
        private:
        };
    }
}
#endif
