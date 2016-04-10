/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.fl.jpa;

import java.io.Serializable;
import javax.persistence.Basic;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author saulario
 */
@Entity
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Usu.findAll", query = "SELECT u FROM Usu u"),
    @NamedQuery(name = "Usu.findByUsucod", query = "SELECT u FROM Usu u WHERE u.usucod = :usucod"),
    @NamedQuery(name = "Usu.findByUsuusr", query = "SELECT u FROM Usu u WHERE u.usuusr = :usuusr"),
    @NamedQuery(name = "Usu.findByUsueml", query = "SELECT u FROM Usu u WHERE u.usueml = :usueml"),
    @NamedQuery(name = "Usu.findByUsupwd", query = "SELECT u FROM Usu u WHERE u.usupwd = :usupwd")})
public class Usu implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    private Long usucod;
    @Basic(optional = false)
    private String usuusr;
    @Basic(optional = false)
    private String usueml;
    @Basic(optional = false)
    private String usupwd;

    public Usu() {
    }

    public Usu(Long usucod) {
        this.usucod = usucod;
    }

    public Usu(Long usucod, String usuusr, String usueml, String usupwd) {
        this.usucod = usucod;
        this.usuusr = usuusr;
        this.usueml = usueml;
        this.usupwd = usupwd;
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
