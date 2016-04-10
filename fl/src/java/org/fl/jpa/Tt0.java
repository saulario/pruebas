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
    @NamedQuery(name = "Tt0.findAll", query = "SELECT t FROM Tt0 t"),
    @NamedQuery(name = "Tt0.findByTt0cod", query = "SELECT t FROM Tt0 t WHERE t.tt0cod = :tt0cod"),
    @NamedQuery(name = "Tt0.findByTt0loc", query = "SELECT t FROM Tt0 t WHERE t.tt0loc = :tt0loc"),
    @NamedQuery(name = "Tt0.findByTt0cypraz", query = "SELECT t FROM Tt0 t WHERE t.tt0cypraz = :tt0cypraz"),
    @NamedQuery(name = "Tt0.findByTt0cypidf", query = "SELECT t FROM Tt0 t WHERE t.tt0cypidf = :tt0cypidf"),
    @NamedQuery(name = "Tt0.findByTt0cyptkr", query = "SELECT t FROM Tt0 t WHERE t.tt0cyptkr = :tt0cyptkr")})
public class Tt0 implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    private Long tt0cod;
    @Basic(optional = false)
    private String tt0loc;
    @Basic(optional = false)
    private String tt0cypraz;
    @Basic(optional = false)
    private String tt0cypidf;
    @Basic(optional = false)
    private String tt0cyptkr;
    @JoinColumn(name = "tt0cypcod", referencedColumnName = "cypcod")
    @ManyToOne(optional = false)
    private Cyp tt0cypcod;
    @JoinColumn(name = "tt0teocod", referencedColumnName = "teocod")
    @ManyToOne(optional = false)
    private Teo tt0teocod;
    @JoinColumn(name = "tt0teacod", referencedColumnName = "teacod")
    @ManyToOne(optional = false)
    private Tea tt0teacod;

    public Tt0() {
    }

    public Tt0(Long tt0cod) {
        this.tt0cod = tt0cod;
    }

    public Tt0(Long tt0cod, String tt0loc, String tt0cypraz, String tt0cypidf, String tt0cyptkr) {
        this.tt0cod = tt0cod;
        this.tt0loc = tt0loc;
        this.tt0cypraz = tt0cypraz;
        this.tt0cypidf = tt0cypidf;
        this.tt0cyptkr = tt0cyptkr;
    }

    public Long getTt0cod() {
        return tt0cod;
    }

    public void setTt0cod(Long tt0cod) {
        this.tt0cod = tt0cod;
    }

    public String getTt0loc() {
        return tt0loc;
    }

    public void setTt0loc(String tt0loc) {
        this.tt0loc = tt0loc;
    }

    public String getTt0cypraz() {
        return tt0cypraz;
    }

    public void setTt0cypraz(String tt0cypraz) {
        this.tt0cypraz = tt0cypraz;
    }

    public String getTt0cypidf() {
        return tt0cypidf;
    }

    public void setTt0cypidf(String tt0cypidf) {
        this.tt0cypidf = tt0cypidf;
    }

    public String getTt0cyptkr() {
        return tt0cyptkr;
    }

    public void setTt0cyptkr(String tt0cyptkr) {
        this.tt0cyptkr = tt0cyptkr;
    }

    public Cyp getTt0cypcod() {
        return tt0cypcod;
    }

    public void setTt0cypcod(Cyp tt0cypcod) {
        this.tt0cypcod = tt0cypcod;
    }

    public Teo getTt0teocod() {
        return tt0teocod;
    }

    public void setTt0teocod(Teo tt0teocod) {
        this.tt0teocod = tt0teocod;
    }

    public Tea getTt0teacod() {
        return tt0teacod;
    }

    public void setTt0teacod(Tea tt0teacod) {
        this.tt0teacod = tt0teacod;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (tt0cod != null ? tt0cod.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Tt0)) {
            return false;
        }
        Tt0 other = (Tt0) object;
        if ((this.tt0cod == null && other.tt0cod != null) || (this.tt0cod != null && !this.tt0cod.equals(other.tt0cod))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "org.fl.jpa.Tt0[ tt0cod=" + tt0cod + " ]";
    }
    
}
