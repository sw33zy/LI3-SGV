package Model;

public class ValidaVendas implements  IValidaVendas{

    /**
     * Função que dada uma linha verifica se esse linha é válida
     * @param token linha do ficheiro
     * @param catCl catálogo dos clientes
     * @param catPd catalogo dos produtos
     * @return boolean true se for válida, false caso contrário
     */
    public static boolean divideLinha(String token, ICatalogoClientes catCl, ICatalogoProdutos catPd) {
        int res1=0, res2=0, res3=0, res4=0, res5=0, res6=0, res7=0, total =0;
        int n = 1;
        boolean vl = false;
        for (String val : token.split(" ")){
            if (n==1) res1 =validaProduto(val,catPd);
            if (n==2) res2 =validaPreco(val);
            if (n==3) res3= validaUnidades(val);
            if (n==4) res4= validaTipo(val);
            if (n==5) res5= validaCliente(val,catCl);
            if (n==6) res6=validaMes (val);
            if (n==7) res7=validaFilial (val);
            n++;
        }
        total = res1 + res2 + res3 + res4 + res5 + res6+ res7;
        if(total == 0) vl=true;
        return vl;
    }

    /**
     * Função que verifica se o código do produto da linha que recebeu existe no catálogo de produtos
     * @param token ID do produto
     * @param catPd catálogo dos produtos
     * @return 0 if true, 1 if false
     */
    public static int validaProduto(String token,ICatalogoProdutos catPd){
        IProduto produto = new Produto(token);
        if(catPd.existsProduct(produto)){
            return 0;
        }
        return 1;
    }

    /**
     * Função que verifica se o código do cliente da linha que recebeu existe no catálogo de clientes
     * @param token ID do cliente
     * @param catCl catálogo dos clientes
     * @return 0 if true, 1 if false
     */
    public static int validaCliente(String token, ICatalogoClientes catCl){
        ICliente cliente = new Cliente(token);
        if(catCl.existsClient(cliente)){
            return  0;
        }
        return 1;
    }

    /**
     * Função que verifica se o preço da linha que recebeu é valido
     * @param preco preço na linha
     * @return 0 if true, 1 if false
     */
    public static int validaPreco(String preco){
        double p = Double.parseDouble(preco);
        if ((p>=0.0) && (p<=999.99)){
            return 0;
        }
        return 1;
    }

    /**
     * Função que verifica se as unidades da linha que recebeu é valido
     * @param unid unidades na linha
     * @return 0 if true, 1 if false
     */
    public static int validaUnidades(String unid){
        int u = Integer.parseInt(unid);
        if ((u>=1) && (u<=200)) {
            return 0;
        }
        return 1;
    }

    /**
     * Função que verifica se o tipo de compra da linha que recebeu é valido
     * @param tipo tipo na linha
     * @return 0 if true, 1 if false
     */
    public static int validaTipo(String tipo){
        String normal = "N";
        String promo = "P";
        if ((tipo.equals(normal.intern())) || (tipo.equals(promo.intern()))){
            return 0;
        }
        return 1;
    }

    /**
     * Função que verifica se o mês da linha que recebeu é valido
     * @param mes mes na linha
     * @return 0 if true, 1 if false
     */
    public static int validaMes(String mes){
        int m = Integer.parseInt(mes);
        if ((m>=1) && (m<=12)){
            return 0;
        }
        return 1;
    }

    /**
     * Função que verifica se a filial da linha que recebeu é valido
     * @param fil filial na linha
     * @return 0 if true, 1 if false
     */
    public static int validaFilial(String fil){
        int f = Integer.parseInt(fil);
        if((f==1) ||(f==2)|| (f==3)) {
            return 0;
        }
        return 1;
    }

}
