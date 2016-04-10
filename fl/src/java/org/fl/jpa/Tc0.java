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
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
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
    @NamedQuery(name = "Tc0.findAll", query = "SELECT t FROM Tc0 t"),
    @NamedQuery(name = "Tc0.findByTc0cod", query = "SELECT t FROM Tc0 t WHERE t.tc0cod = :tc0cod"),
    @NamedQuery(name = "Tc0.findByTc0loc", query = "SELECT t FROM Tc0 t WHERE t.tc0loc = :tc0loc"),
    @NamedQuery(name = "Tc0.findByTc0cypraz", query = "SELECT t FROM Tc0 t WHERE t.tc0cypraz = :tc0cypraz"),
    @NamedQuery(name = "Tc0.findByTc0cypidf", query = "SELECT t FROM Tc0 t WHERE t.tc0cypidf = :tc0cypidf"),
    @NamedQuery(name = "Tc0.findByTc0cyptkr", query = "SELECT t FROM Tc0 t WHERE t.tc0cyptkr = :tc0cyptkr")})
public class Tc0 implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    private Long tc0cod;
    @Basic(optional = false)
    private String tc0loc;
    @Basic(optional = false)
    private String tc0cypraz;
    @Basic(optional = false)
    private String tc0cypidf;
    @Basic(optional = false)
    private String tc0cyptkr;
    @JoinColumn(name = "tc0cypcod", referencedColumnName = "cypcod")
    @ManyToOne(optional = false)
    private Cyp tc0cypcod;
    @JoinColumn(name = "tc0teocod", referencedColumnName = "teocod")
    @ManyToOne(optional = false)
    private Teo tc0teocod;
    @JoinColumn(name = "tc0teacod", referencedColumnName = "teacod")
    @ManyToOne(optional = false)
    private Tea tc0teacod;

    public Tc0() {
    }

    public Tc0(Long tc0cod) {
        this.tc0cod = tc0cod;
    }

    public Tc0(Long tc0cod, String tc0loc, String tc0cypraz, String tc0cypidf, String tc0cyptkr) {
        this.tc0cod = tc0cod;
        this.tc0loc = tc0loc;
        this.tc0cypraz = tc0cypraz;
        this.tc0cypidf = tc0cypidf;
        this.tc0cyptkr = tc0cyptkr;
    }

    public Long getTc0cod() {
        return tc0cod;
    }

    public void setTc0cod(Long tc0cod) {
        this.tc0cod = tc0cod;
    }

    public String getTc0loc() {
        return tc0loc;
    }

    public void setTc0loc(String tc0loc) {
        this.tc0loc = tc0loc;
    }

    public String getTc0cypraz() {
        return tc0cypraz;
    }

    public void setTc0cypraz(String tc0cypraz) {
        this.tc0cypraz = tc0cypraz;
    }

    public String getTc0cypidf() {
        return tc0cypidf;
    }

    public void setTc0cypidf(String tc0cypidf) {
        this.tc0cypidf = tc0cypidf;
    }

    public String getTc0cyptkr() {
        return tc0cyptkr;
    }

    public void setTc0cyptkr(String tc0cyptkr) {
        this.tc0cyptkr = tc0cyptkr;
    }

    public Cyp getTc0cypcod() {
        return tc0cypcod;
    }

    public void setTc0cypcod(Cyp tc0cypcod) {
        this.tc0cypcod = tc0cypcod;
    }

    public Teo getTc0teocod() {
        return tc0teocod;
    }

    public void setTc0teocod(Teo tc0teocod) {
        this.tc0teocod = tc0teocod;
    }

    public Tea getTc0teacod() {
        return tc0teacod;
    }

    public void setTc0teacod(Tea tc0teacod) {
        this.tc0teacod = tc0teacod;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (tc0cod != null ? tc0cod.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Tc0)) {
            return false;
        }
        Tc0 other = (Tc0) object;
        if ((this.tc0cod == null && other.tc0cod != null) || (this.tc0cod != null && !this.tc0cod.equals(other.tc0cod))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "org.fl.jpa.Tc0[ tc0cod=" + tc0cod + " ]";
    }
    
}
