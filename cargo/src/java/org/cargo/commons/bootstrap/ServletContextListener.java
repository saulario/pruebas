package org.cargo.commons.bootstrap;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.UUID;
import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.servlet.ServletContextEvent;
import javax.servlet.annotation.WebListener;
import javax.sql.DataSource;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.cargo.bl.jpa.Usu;

@WebListener
public class ServletContextListener implements javax.servlet.ServletContextListener {

    private static EntityManagerFactory emf = null;
    private static final Logger log = LogManager.getLogger();
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
            DataSource ds = (DataSource) ic.lookup("java:comp/env/jdbc/cargoDS");
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

        log.info("+-----> Creando EntityManagerFactory");
        try {

            emf = Persistence.createEntityManagerFactory(CARGO_PU);

            log.info("+-----> Testeando la conexión con la base de datos");
            EntityManager em = emf.createEntityManager();
//            List usus = em.createQuery("select usu from Usu as usu").setMaxResults(1)
//                    .getResultList();
//            for (Object usu : usus) {
//                log.info("\t\t(usuusr): " + ((Usu)usu).getUsuusr());
//            }

            Usu usu = em.find(Usu.class, 0L);
            if (usu != null) {
                log.info("\t\t(usuusr): " + ((Usu) usu).getUsuusr());
            }
            usu = em.find(Usu.class, 1L);
            if (usu != null) {
                em.getTransaction().begin();
                log.info("\t\t(usuusr): " + ((Usu) usu).getUsuusr());
                usu.setUsupwd(UUID.randomUUID().toString());
                em.getTransaction().commit();
            }

            em.close();
        } catch (Throwable e) {
            log.error(this, e);
        }

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
