package org.cargo.bl.jpa;
// Generated 23-abr-2016 20:32:26 by Hibernate Tools 4.3.1


import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.Table;
import javax.persistence.Version;

/**
 * Tca generated by hbm2java
 */
@Entity
@Table(name="tca"
    ,catalog="cargo"
)
public class Tca  implements java.io.Serializable {


     private long tcacod;
     private long version;
     private Cli cli;
     private Teo teo;
     private String tcaloc;
     private String tcacliraz;
     private String tcacliidf;
     private String tcaclitkr;

    public Tca() {
    }

    public Tca(long tcacod, Cli cli, Teo teo, String tcaloc, String tcacliraz, String tcacliidf, String tcaclitkr) {
       this.tcacod = tcacod;
       this.cli = cli;
       this.teo = teo;
       this.tcaloc = tcaloc;
       this.tcacliraz = tcacliraz;
       this.tcacliidf = tcacliidf;
       this.tcaclitkr = tcaclitkr;
    }
   
     @Id 

    
    @Column(name="tcacod", unique=true, nullable=false)
    public long getTcacod() {
        return this.tcacod;
    }
    
    public void setTcacod(long tcacod) {
        this.tcacod = tcacod;
    }

    @Version
    @Column(name="version", nullable=false)
    public long getVersion() {
        return this.version;
    }
    
    public void setVersion(long version) {
        this.version = version;
    }

@ManyToOne(fetch=FetchType.LAZY)
    @JoinColumn(name="tcaclicod", nullable=false)
    public Cli getCli() {
        return this.cli;
    }
    
    public void setCli(Cli cli) {
        this.cli = cli;
    }

@ManyToOne(fetch=FetchType.LAZY)
    @JoinColumn(name="tcateocod", nullable=false)
    public Teo getTeo() {
        return this.teo;
    }
    
    public void setTeo(Teo teo) {
        this.teo = teo;
    }

    
    @Column(name="tcaloc", nullable=false, length=20)
    public String getTcaloc() {
        return this.tcaloc;
    }
    
    public void setTcaloc(String tcaloc) {
        this.tcaloc = tcaloc;
    }

    
    @Column(name="tcacliraz", nullable=false, length=80)
    public String getTcacliraz() {
        return this.tcacliraz;
    }
    
    public void setTcacliraz(String tcacliraz) {
        this.tcacliraz = tcacliraz;
    }

    
    @Column(name="tcacliidf", nullable=false, length=20)
    public String getTcacliidf() {
        return this.tcacliidf;
    }
    
    public void setTcacliidf(String tcacliidf) {
        this.tcacliidf = tcacliidf;
    }

    
    @Column(name="tcaclitkr", nullable=false, length=5)
    public String getTcaclitkr() {
        return this.tcaclitkr;
    }
    
    public void setTcaclitkr(String tcaclitkr) {
        this.tcaclitkr = tcaclitkr;
    }




}


