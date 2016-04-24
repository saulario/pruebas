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
 * Pro generated by hbm2java
 */
@Entity
@Table(name="pro"
    ,catalog="cargo"
)
public class Pro  implements java.io.Serializable {


     private long procod;
     private long version;
     private String proraz;
     private String proidf;
     private String protkr;
     private Set<Tta> ttas = new HashSet<Tta>(0);

    public Pro() {
    }

	
    public Pro(long procod, String proraz, String proidf, String protkr) {
        this.procod = procod;
        this.proraz = proraz;
        this.proidf = proidf;
        this.protkr = protkr;
    }
    public Pro(long procod, String proraz, String proidf, String protkr, Set<Tta> ttas) {
       this.procod = procod;
       this.proraz = proraz;
       this.proidf = proidf;
       this.protkr = protkr;
       this.ttas = ttas;
    }
   
     @Id 

    
    @Column(name="procod", unique=true, nullable=false)
    public long getProcod() {
        return this.procod;
    }
    
    public void setProcod(long procod) {
        this.procod = procod;
    }

    @Version
    @Column(name="version", nullable=false)
    public long getVersion() {
        return this.version;
    }
    
    public void setVersion(long version) {
        this.version = version;
    }

    
    @Column(name="proraz", nullable=false, length=80)
    public String getProraz() {
        return this.proraz;
    }
    
    public void setProraz(String proraz) {
        this.proraz = proraz;
    }

    
    @Column(name="proidf", nullable=false, length=20)
    public String getProidf() {
        return this.proidf;
    }
    
    public void setProidf(String proidf) {
        this.proidf = proidf;
    }

    
    @Column(name="protkr", nullable=false, length=5)
    public String getProtkr() {
        return this.protkr;
    }
    
    public void setProtkr(String protkr) {
        this.protkr = protkr;
    }

@OneToMany(fetch=FetchType.LAZY, mappedBy="pro")
    public Set<Tta> getTtas() {
        return this.ttas;
    }
    
    public void setTtas(Set<Tta> ttas) {
        this.ttas = ttas;
    }




}

