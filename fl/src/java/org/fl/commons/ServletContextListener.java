package org.fl.commons;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.servlet.ServletContextEvent;
import javax.servlet.annotation.WebListener;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.fl.jpa.Usu;

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
    public synchronized void contextInitialized(ServletContextEvent sce) {
        log.info("************************************************");
        log.info("* Desplegando Freightliner/Cargo");
        log.info("*");
        
        log.info("+-----> Creando EntityManagerFactory");
        emf = Persistence.createEntityManagerFactory(CARGO_PU);
        
        log.info("+-----> Testeando la conexión con la base de datos");
        EntityManager em = emf.createEntityManager();
        List<Usu> usus = em.createQuery("select usu from Usu as usu", Usu.class).setMaxResults(1).getResultList();
        em.close();
        
        log.info("*");
        log.info("************************************************");
    }

    /**
     *
     * @param sce
     */
    @Override
    public void contextDestroyed(ServletContextEvent sce) {
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
        log.info(("-----> Inicio"));
        if (emf == null) {
            throw new IllegalStateException("Contexto de persistencia no inicializado");
        }
        EntityManager em = emf.createEntityManager();
        log.info("<----- Fin");
        return em;
    }
    
}
