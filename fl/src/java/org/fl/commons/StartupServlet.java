package org.fl.commons;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.sql.DataSource;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 *
 * @author saulario
 */
public class StartupServlet extends HttpServlet {

    public static final Logger log = LogManager.getLogger();

    /**
     *
     * @throws ServletException
     */
    @Override
    public void init() throws ServletException {
        log.info("-----> Inicio");

        Connection c = null;
        try {
            Context ic = new InitialContext();
            DataSource ds = (DataSource) ic.lookup("java:/comp/env/jdbc/flDS");
            c = ds.getConnection();

            PreparedStatement ps = c.prepareStatement("select * from pepito");
            ps.executeQuery();
            ps.close();

            c.close();
        } catch (NamingException | SQLException e) {
            log.error(this, e);
        }

        log.info("<----- Fin");
    }

}
