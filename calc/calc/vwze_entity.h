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
            int docpes; /*  */
            double docvol; /*  */
            int docpef; /*  */
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
            int dodpes; /*  */
            double dodvol; /*  */
            int dodpef; /*  */
            std::string dodkey; /*  */
            Dod();
            ~Dod();
            bool operator==(const Dod &);
        private:
        };

        struct Doe {
        public:
            long doecod; /*  */
            std::string doerel; /*  */
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
            int doepes; /*  */
            double doevol; /*  */
            int doepef; /*  */
            int doecnt; /*  */
            double doepun; /*  */
            double doetot; /*  */
            std::string doekey; /*  */
            Doe();
            ~Doe();
            bool operator==(const Doe &);
        private:
        };

        struct Flt {
        public:
            std::string fltcod; /*  */
            Flt();
            ~Flt();
            bool operator==(const Flt &);
        private:
        };

        struct Kcc {
        public:
            std::string kcccod;
            std::string kccnom;
            Kcc();
            ~Kcc();
            bool operator==(const Kcc &);
        private:
        };

        struct Kosten {
        public:
            std::string exped; /*  */
            std::string relevanz; /*  */
            std::string wewa; /*  */
            std::string gebiet; /*  */
            std::string sender; /*  */
            std::string receiver; /*  */
            std::string planta; /*  */
            int menge; /*  */
            double kosten; /*  */
            double fratch; /*  */
            Kosten();
            ~Kosten();
            std::string getTransportista(void) const;
            void setTransportista(const std::string & transportista);
            bool isNullTransportista(void) const;
            void setNullTransportista(void);
            std::string getEscenario(void) const;
            void setEscenario(const std::string & escenario);
            bool isNullEscenario(void) const;
            void setNullEscenario(void);
            bool operator==(const Kosten &);
        private:
            std::string * transportista; /*  */
            std::string * escenario; /*  */
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
            double rfdmin; /*  */
            double rfdmef; /*  */
            double rfdpun; /*  */
            Rfd();
            ~Rfd();
            bool operator==(const Rfd &);
        private:
        };

        struct Todo {
        public:
            std::string documento; /*  */
            std::string relevancia; /*  */
            tntdb::Datetime fecha; /*  */
            std::string orgpais; /*  */
            std::string orgcp; /*  */
            std::string orgzon; /*  */
            std::string orgpob; /*  */
            std::string despais; /*  */
            std::string descp; /*  */
            std::string deszon; /*  */
            std::string despob; /*  */
            std::string flujo; /*  */
            std::string proveedor; /*  */
            std::string planta; /*  */
            int peso; /*  */
            double volumen; /*  */
            int pesofac; /*  */
            std::string ruta; /*  */
            std::string kcc; /*  */
            std::string nombreprov; /*  */
            Todo();
            ~Todo();
            bool operator==(const Todo &);
        private:
        };

        struct Vkosten {
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
            int docpes; /*  */
            double docvol; /*  */
            int docpef; /*  */
            std::string exped; /*  */
            std::string relevanz; /*  */
            std::string wewa; /*  */
            std::string gebiet; /*  */
            std::string sender; /*  */
            std::string receiver; /*  */
            std::string planta; /*  */
            int menge; /*  */
            double kosten; /*  */
            double fratch; /*  */
            Vkosten();
            ~Vkosten();
            std::string getTransportista(void) const;
            void setTransportista(const std::string & transportista);
            bool isNullTransportista(void) const;
            void setNullTransportista(void);
            std::string getEscenario(void) const;
            void setEscenario(const std::string & escenario);
            bool isNullEscenario(void) const;
            void setNullEscenario(void);
            bool operator==(const Vkosten &);
        private:
            std::string * transportista; /*  */
            std::string * escenario; /*  */
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
