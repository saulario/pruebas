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
@Table(name = "tea")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Tea.findAll", query = "SELECT t FROM Tea t"),
    @NamedQuery(name = "Tea.findByVersion", query = "SELECT t FROM Tea t WHERE t.version = :version"),
    @NamedQuery(name = "Tea.findByTeacod", query = "SELECT t FROM Tea t WHERE t.teacod = :teacod"),
    @NamedQuery(name = "Tea.findByTeades", query = "SELECT t FROM Tea t WHERE t.teades = :teades"),
    @NamedQuery(name = "Tea.findByTeadef", query = "SELECT t FROM Tea t WHERE t.teadef = :teadef")})
public class Tea implements Serializable {

    private static final long serialVersionUID = 1L;
    @Basic(optional = false)
    @Column(name = "version")
    private long version;
    @Id
    @Basic(optional = false)
    @Column(name = "teacod")
    private String teacod;
    @Basic(optional = false)
    @Column(name = "teades")
    private String teades;
    @Basic(optional = false)
    @Column(name = "teadef")
    private short teadef;

    public Tea() {
    }

    public Tea(String teacod) {
        this.teacod = teacod;
    }

    public Tea(String teacod, long version, String teades, short teadef) {
        this.teacod = teacod;
        this.version = version;
        this.teades = teades;
        this.teadef = teadef;
    }

    public long getVersion() {
        return version;
    }

    public void setVersion(long version) {
        this.version = version;
    }

    public String getTeacod() {
        return teacod;
    }

    public void setTeacod(String teacod) {
        this.teacod = teacod;
    }

    public String getTeades() {
        return teades;
    }

    public void setTeades(String teades) {
        this.teades = teades;
    }

    public short getTeadef() {
        return teadef;
    }

    public void setTeadef(short teadef) {
        this.teadef = teadef;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (teacod != null ? teacod.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Tea)) {
            return false;
        }
        Tea other = (Tea) object;
        if ((this.teacod == null && other.teacod != null) || (this.teacod != null && !this.teacod.equals(other.teacod))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "org.fl.jpa.Tea[ teacod=" + teacod + " ]";
    }
    
}
