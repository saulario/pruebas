package org.cargo.bl.jpa;
// Generated 23-abr-2016 20:32:26 by Hibernate Tools 4.3.1


import java.util.HashSet;
import java.util.Set;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.Id;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.persistence.Version;

/**
 * Cli generated by hbm2java
 */
@Entity
@Table(name="cli"
    ,catalog="cargo"
)
public class Cli  implements java.io.Serializable {


     private long clicod;
     private long version;
     private String cliraz;
     private String cliidf;
     private String clitkr;
     private Set<Tca> tcas = new HashSet<Tca>(0);

    public Cli() {
    }

	
    public Cli(long clicod, String cliraz, String cliidf, String clitkr) {
        this.clicod = clicod;
        this.cliraz = cliraz;
        this.cliidf = cliidf;
        this.clitkr = clitkr;
    }
    public Cli(long clicod, String cliraz, String cliidf, String clitkr, Set<Tca> tcas) {
       this.clicod = clicod;
       this.cliraz = cliraz;
       this.cliidf = cliidf;
       this.clitkr = clitkr;
       this.tcas = tcas;
    }
   
     @Id 

    
    @Column(name="clicod", unique=true, nullable=false)
    public long getClicod() {
        return this.clicod;
    }
    
    public void setClicod(long clicod) {
        this.clicod = clicod;
    }

    @Version
    @Column(name="version", nullable=false)
    public long getVersion() {
        return this.version;
    }
    
    public void setVersion(long version) {
        this.version = version;
    }

    
    @Column(name="cliraz", nullable=false, length=80)
    public String getCliraz() {
        return this.cliraz;
    }
    
    public void setCliraz(String cliraz) {
        this.cliraz = cliraz;
    }

    
    @Column(name="cliidf", nullable=false, length=20)
    public String getCliidf() {
        return this.cliidf;
    }
    
    public void setCliidf(String cliidf) {
        this.cliidf = cliidf;
    }

    
    @Column(name="clitkr", nullable=false, length=5)
    public String getClitkr() {
        return this.clitkr;
    }
    
    public void setClitkr(String clitkr) {
        this.clitkr = clitkr;
    }

@OneToMany(fetch=FetchType.LAZY, mappedBy="cli")
    public Set<Tca> getTcas() {
        return this.tcas;
    }
    
    public void setTcas(Set<Tca> tcas) {
        this.tcas = tcas;
    }




}

