package org.cargo.bl.jpa;
// Generated 23-abr-2016 20:32:26 by Hibernate Tools 4.3.1


import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Version;

/**
 * Usu generated by hbm2java
 */
@Entity
@Table(name="usu"
    ,catalog="cargo"
)
public class Usu  implements java.io.Serializable {


     private long usucod;
     private long version;
     private String usuusr;
     private String usueml;
     private String usunom;
     private String usupwd;

    public Usu() {
    }

    public Usu(long usucod, String usuusr, String usueml, String usunom, String usupwd) {
       this.usucod = usucod;
       this.usuusr = usuusr;
       this.usueml = usueml;
       this.usunom = usunom;
       this.usupwd = usupwd;
    }
   
     @Id 

    
    @Column(name="usucod", unique=true, nullable=false)
    public long getUsucod() {
        return this.usucod;
    }
    
    public void setUsucod(long usucod) {
        this.usucod = usucod;
    }

    @Version
    @Column(name="version", nullable=false)
    public long getVersion() {
        return this.version;
    }
    
    public void setVersion(long version) {
        this.version = version;
    }

    
    @Column(name="usuusr", nullable=false, length=10)
    public String getUsuusr() {
        return this.usuusr;
    }
    
    public void setUsuusr(String usuusr) {
        this.usuusr = usuusr;
    }

    
    @Column(name="usueml", nullable=false, length=200)
    public String getUsueml() {
        return this.usueml;
    }
    
    public void setUsueml(String usueml) {
        this.usueml = usueml;
    }

    
    @Column(name="usunom", nullable=false, length=200)
    public String getUsunom() {
        return this.usunom;
    }
    
    public void setUsunom(String usunom) {
        this.usunom = usunom;
    }

    
    @Column(name="usupwd", nullable=false, length=200)
    public String getUsupwd() {
        return this.usupwd;
    }
    
    public void setUsupwd(String usupwd) {
        this.usupwd = usupwd;
    }




}

