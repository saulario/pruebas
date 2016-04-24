/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.fl.jpa;

import java.io.Serializable;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author saulario
 */
@Entity
@Table(name = "usu")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Usu.findAll", query = "SELECT u FROM Usu u"),
    @NamedQuery(name = "Usu.findByVersion", query = "SELECT u FROM Usu u WHERE u.version = :version"),
    @NamedQuery(name = "Usu.findByUsucod", query = "SELECT u FROM Usu u WHERE u.usucod = :usucod"),
    @NamedQuery(name = "Usu.findByUsuusr", query = "SELECT u FROM Usu u WHERE u.usuusr = :usuusr"),
    @NamedQuery(name = "Usu.findByUsueml", query = "SELECT u FROM Usu u WHERE u.usueml = :usueml"),
    @NamedQuery(name = "Usu.findByUsunom", query = "SELECT u FROM Usu u WHERE u.usunom = :usunom"),
    @NamedQuery(name = "Usu.findByUsupwd", query = "SELECT u FROM Usu u WHERE u.usupwd = :usupwd")})
public class Usu implements Serializable {

    private static final long serialVersionUID = 1L;
    @Basic(optional = false)
    @Column(name = "version")
    private long version;
    @Id
    @Basic(optional = false)
    @Column(name = "usucod")
    private Long usucod;
    @Basic(optional = false)
    @Column(name = "usuusr")
    private String usuusr;
    @Basic(optional = false)
    @Column(name = "usueml")
    private String usueml;
    @Basic(optional = false)
    @Column(name = "usunom")
    private String usunom;
    @Basic(optional = false)
    @Column(name = "usupwd")
    private String usupwd;

    public Usu() {
    }

    public Usu(Long usucod) {
        this.usucod = usucod;
    }

    public Usu(Long usucod, long version, String usuusr, String usueml, String usunom, String usupwd) {
        this.usucod = usucod;
        this.version = version;
        this.usuusr = usuusr;
        this.usueml = usueml;
        this.usunom = usunom;
        this.usupwd = usupwd;
    }

    public long getVersion() {
        return version;
    }

    public void setVersion(long version) {
        this.version = version;
    }

    public Long getUsucod() {
        return usucod;
    }

    public void setUsucod(Long usucod) {
        this.usucod = usucod;
    }

    public String getUsuusr() {
        return usuusr;
    }

    public void setUsuusr(String usuusr) {
        this.usuusr = usuusr;
    }

    public String getUsueml() {
        return usueml;
    }

    public void setUsueml(String usueml) {
        this.usueml = usueml;
    }

    public String getUsunom() {
        return usunom;
    }

    public void setUsunom(String usunom) {
        this.usunom = usunom;
    }

    public String getUsupwd() {
        return usupwd;
    }

    public void setUsupwd(String usupwd) {
        this.usupwd = usupwd;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (usucod != null ? usucod.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Usu)) {
            return false;
        }
        Usu other = (Usu) object;
        if ((this.usucod == null && other.usucod != null) || (this.usucod != null && !this.usucod.equals(other.usucod))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "org.fl.jpa.Usu[ usucod=" + usucod + " ]";
    }
    
}
