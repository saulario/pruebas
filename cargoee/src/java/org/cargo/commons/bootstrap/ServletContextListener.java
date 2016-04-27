/*
 * Freightliner/cargo
 *
 * Copyright (C) 2015..  Saul Correas Subias 
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */
package org.cargo.commons.bootstrap;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.servlet.ServletContextEvent;
import javax.servlet.annotation.WebListener;
import javax.sql.DataSource;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;


@WebListener
public class ServletContextListener implements javax.servlet.ServletContextListener {

    private static EntityManagerFactory emf = null;
    private static final Logger log = LogManager.getLogger(ServletContextListener.class);
    private static final String CARGO_PU = "cargoPU";

    /**
     *
     * @param sce
     */
    @Override
    public synchronized void contextInitialized(final ServletContextEvent sce) {
        log.info("************************************************");
        log.info("* Desplegando Freightliner/Cargo");
        log.info("*");

        log.info("+-----> Comprobando JNDI");
        try {
            Context ic = new InitialContext();
            DataSource ds = (DataSource) ic.lookup("java:/jdbc/cargoDS");
            Connection c = ds.getConnection();
            ResultSet rs = c.prepareStatement("select now()").executeQuery();
            while (rs.next()) {
                log.info("\t\t(now): " + rs.getObject(1).toString());
            }
            rs.close();
            c.close();
        } catch (NamingException | SQLException ex) {
            log.error(this, ex);
        }

//        log.info("+-----> Creando EntityManagerFactory");
//        EntityManager em = null;
//        try {
//
//            emf = Persistence.createEntityManagerFactory(CARGO_PU);
//
//            log.info("+-----> Testeando la conexión con la base de datos");
//            em = emf.createEntityManager();
//
//            Usu usu = em.find(Usu.class, 1L);
//            if (usu != null) {
//                log.info("\t\t(usuusr): " + ((Usu) usu).getUsuusr());
//            }
//
//        } catch (Throwable e) {
//            log.error(this, e);
//        } finally {
//            if (em != null) {
//                em.close();
//            }
//        }

        log.info("+-----> Comprobando Interceptores");
        
        ClaseAuditada c = new ClaseAuditada();
        c.metodoAuditado();

        log.info("*");
        log.info("************************************************");
    }

    /**
     *
     * @param sce
     */
    @Override
    public void contextDestroyed(final ServletContextEvent sce) {
        log.info("************************************************");
        log.info("* Replegando Freightliner/cargo");
        log.info("*");

        log.info("+-----> Cerrando EntityManagerFactory");
        if (emf != null) {
            emf.close();
        }

        log.info("*");
        log.info("************************************************");

    }

    /**
     *
     * @return
     */
    public static EntityManager getEntityManager() {
        log.info("-----> Inicio");
        if (emf == null) {
            throw new IllegalStateException("Contexto de persistencia no inicializado");
        }
        EntityManager em = emf.createEntityManager();
        log.info("<----- Fin");
        return em;
    }

}
