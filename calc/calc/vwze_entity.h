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
      std::string docorgloc; /*  */
      std::string docorgzon; /*  */
      std::string docorgpcp; /*  */
      std::string docorgpob; /*  */
      std::string docdesloc; /*  */
      std::string docdeszon; /*  */
      std::string docdespcp; /*  */
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
      bool operator == (const Doc &);
    private:
    };
    struct Dod {
    public:
      long dodcod; /*  */
      std::string dodrel; /*  */
      std::string dodexp; /*  */
      int dodtip; /*  */
      tntdb::Date dodfec; /*  */
      std::string dodorgloc; /*  */
      std::string dodorgzon; /*  */
      std::string dodorgpcp; /*  */
      std::string dodorgpob; /*  */
      std::string doddesloc; /*  */
      std::string doddeszon; /*  */
      std::string doddespcp; /*  */
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
      bool operator == (const Dod &);
    private:
    };
    struct Doe {
    public:
      long doecod; /*  */
      std::string doerel; /*  */
      int doetip; /*  */
      tntdb::Date doefec; /*  */
      std::string doeorgloc; /*  */
      std::string doeorgzon; /*  */
      std::string doeorgpcp; /*  */
      std::string doeorgpob; /*  */
      std::string doedesloc; /*  */
      std::string doedeszon; /*  */
      std::string doedespcp; /*  */
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
      bool operator == (const Doe &);
    private:
    };
    struct Elt {
    public:
      int eltcod; /*  */
      std::string eltorg; /* Valor en doc */
      std::string eltdes; /* Valor en rfc */
      Elt();
      ~Elt();
      bool operator == (const Elt &);
    private:
    };
    struct Flt {
    public:
      std::string fltcod; /*  */
      Flt();
      ~Flt();
      bool operator == (const Flt &);
    private:
    };
    struct Kcc {
    public:
      std::string kcccod; /* Codigo interno */
      std::string kccnom; /* Descripción */
      Kcc();
      ~Kcc();
      bool operator == (const Kcc &);
    private:
    };
    struct Kosten {
    public:
      std::string auftragsnummer; /*  */
      std::string relevanz; /*  */
      std::string wewa; /*  */
      std::string gebiet; /*  */
      std::string senderLokationsnummer; /*  */
      std::string empfangerLokationsnummer; /*  */
      std::string werk; /*  */
      std::string transportlisteName; /*  */
      std::string szenariolisteName; /*  */
      int sumMenge; /*  */
      double sumKosten; /*  */
      double sumFracht; /*  */
      double hl; /*  */
      Kosten();
      ~Kosten();
      bool operator == (const Kosten &);
    private:
    };
    struct Pro {
    public:
      std::string produn; /*  */
      std::string proraz; /*  */
      Pro();
      ~Pro();
      bool operator == (const Pro &);
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
      bool operator == (const Rfc &);
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
      bool operator == (const Rfd &);
    private:
    };
    struct Sendungsdate {
    public:
      std::string auftragsnummer; /*  */
      tntdb::Datetime datum; /*  */
      std::string relevanz; /*  */
      std::string senderLokationsnummer; /*  */
      std::string senderLand; /*  */
      std::string senderPlz; /*  */
      std::string senderOrt; /*  */
      std::string empfangerLokationsnummer; /*  */
      std::string empfangerLand; /*  */
      std::string empfangerPlz; /*  */
      std::string empfangerOrt; /*  */
      std::string wewa; /*  */
      std::string werk; /*  */
      std::string routing; /*  */
      double brutto; /*  */
      double volumen; /*  */
      int menge; /*  */
      Sendungsdate();
      ~Sendungsdate();
      bool operator == (const Sendungsdate &);
    private:
    };
    struct Transport {
    public:
      int id; /*  */
      std::string auftragsnummer; /*  */
      int transportId; /*  */
      std::string wewa; /*  */
      std::string werk; /*  */
      std::string relevanz; /*  */
      std::string gebiet; /*  */
      std::string transportbenne; /*  */
      std::string senderLokationsnummer; /*  */
      std::string empfangerLokationsnummer; /*  */
      int sumMenge; /*  */
      Transport();
      ~Transport();
      bool operator == (const Transport &);
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
      bool operator == (const Zon &);
    private:
    };
    struct Zoo {
    public:
      long zoocod; /*  */
      std::string zoozoncod; /*  */
      std::string zoopcp; /*  */
      Zoo();
      ~Zoo();
      bool operator == (const Zoo &);
    private:
    };
  }
}
#endif
