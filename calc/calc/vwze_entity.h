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
            std::string dockcc; /*  */
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
            int dodtip; /*  */
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

        struct Doe {
        public:
            long doecod; /*  */
            int doetip; /*  */
            tntdb::Date doefec; /*  */
            std::string doeorgzon; /*  */
            std::string doeorgpob; /*  */
            std::string doedeszon; /*  */
            std::string doedespob; /*  */
            std::string doeflu; /*  */
            std::string doeexp; /*  */
            std::string doedun; /*  */
            std::string doepro; /*  */
            double doepes; /*  */
            double doevol; /*  */
            double doepef; /*  */
            int doecnt; /*  */
            double doepun; /*  */
            double doetot; /*  */
            Doe();
            ~Doe();
            bool operator==(const Doe &);
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

        struct Rfc {
        public:
            long rfccod; /*  */
            std::string rfcrul; /*  */
            double rfcmin; /*  */
            int rfckmt; /*  */
            std::string rfczon; /*  */
            Rfc();
            ~Rfc();
            bool operator==(const Rfc &);
        private:
        };

        struct Rfd {
        public:
            long rfdcod; /*  */
            long rfdrfccod; /*  */
            double rfdmax; /*  */
            double rfdpun; /*  */
            Rfd();
            ~Rfd();
            bool operator==(const Rfd &);
        private:
        };

        struct Zon {
        public:
            std::string zoncod; /*  */
            std::string zondes; /*  */
            double zonman; /*  */
            double zontte; /*  */
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
