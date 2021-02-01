package Controller;

import Model.IGestaoVendas;
import View.IView;

import java.io.IOException;

public interface IController {
    void setModel(IGestaoVendas sgv);
    void setView(IView view);
    void run() throws IOException, ClassNotFoundException, InterruptedException;
}
