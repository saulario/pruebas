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
@Table(name = "emp")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Emp.findAll", query = "SELECT e FROM Emp e"),
    @NamedQuery(name = "Emp.findByVersion", query = "SELECT e FROM Emp e WHERE e.version = :version"),
    @NamedQuery(name = "Emp.findByEmpcod", query = "SELECT e FROM Emp e WHERE e.empcod = :empcod"),
    @NamedQuery(name = "Emp.findByEmpraz", query = "SELECT e FROM Emp e WHERE e.empraz = :empraz"),
    @NamedQuery(name = "Emp.findByEmpidf", query = "SELECT e FROM Emp e WHERE e.empidf = :empidf")})
public class Emp implements Serializable {

    private static final long serialVersionUID = 1L;
    @Basic(optional = false)
    @Column(name = "version")
    private long version;
    @Id
    @Basic(optional = false)
    @Column(name = "empcod")
    private Long empcod;
    @Basic(optional = false)
    @Column(name = "empraz")
    private String empraz;
    @Basic(optional = false)
    @Column(name = "empidf")
    private String empidf;

    public Emp() {
    }

    public Emp(Long empcod) {
        this.empcod = empcod;
    }

    public Emp(Long empcod, long version, String empraz, String empidf) {
        this.empcod = empcod;
        this.version = version;
        this.empraz = empraz;
        this.empidf = empidf;
    }

    public long getVersion() {
        return version;
    }

    public void setVersion(long version) {
        this.version = version;
    }

    public Long getEmpcod() {
        return empcod;
    }

    public void setEmpcod(Long empcod) {
        this.empcod = empcod;
    }

    public String getEmpraz() {
        return empraz;
    }

    public void setEmpraz(String empraz) {
        this.empraz = empraz;
    }

    public String getEmpidf() {
        return empidf;
    }

    public void setEmpidf(String empidf) {
        this.empidf = empidf;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (empcod != null ? empcod.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Emp)) {
            return false;
        }
        Emp other = (Emp) object;
        if ((this.empcod == null && other.empcod != null) || (this.empcod != null && !this.empcod.equals(other.empcod))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "org.fl.jpa.Emp[ empcod=" + empcod + " ]";
    }
    
}
