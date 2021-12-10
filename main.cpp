#include <iostream>
#include <iomanip>

using namespace std;
void menu();
void Admin();
void Ventas();
void Altas();
void Bajas();
void Consultas();
void Modificar();
void Cortedecaja();
void AdministradorCuentas();
void MostrarInventario();
void CambiarStProd(string);
void CambiarStCuent(string);
void AltaCU();
void BajaCU();
void ConsultasCU();
void ModiCU();
void MostrarCU();
void Iniciar();
int BuscarCuent(string temp_ad);
int Buscar(string prod); 

struct Productos{
    string nombre;
    int id;
    int ex;
    int nr;
    double pc;
    double pv;
    bool st;
};

struct Cuentas{
    string nombre;
    int pass;
    bool st;
    bool perm;
};

Productos product[10] = {{"leche", 1, 16, 5, 12.35, 15.5, true},{"pan", 2, 18, 6, 5.5, 7.95, true},{"agua", 3, 12, 4, 13.39, 18.55, true},{"huevo", 4, 20, 7, 22.4, 30.39, true},{"refresco", 5, 30, 8, 10.99, 14.75, true}};
Cuentas cuent[10] = {{"admin", 123, true, true}, {"vend1", 123, true, false}, {"vend2", 123, true, false}};
int tlcuentas=3;
int val;
int total=5;

struct venta{
    string Producto[10];
    int cantidad[10];
    float subtotal[10];
    float total;
};

venta ListaVentas[30];



int main(){  

  int op;
  do{
    val=0;  
    cout<<"\t\tBienvenido"<<endl;
    cout<<"Menu Principal:" << endl;
    cout<<"1.Administrador" << endl;
    cout<<"2.Ventas" << endl;
    cout<<"3.Salir" << endl;
    cin>>op;
    switch (op){
	    case 1: Admin ();
	    break;
	    case 2: Ventas ();
	    break;
	    case 3: cout << "Saliendo del Sistema." << endl;
        break;
	    default: cout << "Opcion invalida" << endl;
	}
  }while (op!=3);
  return 0;
}


void Admin(){  
    int pos;
    int op, i;
    int temp_con;
    string temp_cuent;
    op = 0;
    i = 0;
    cout<<"Para acceder porfavor ingrese: "<<endl;
    cout<<endl;
    do{
        cout<<"Nombre de Usuario: ";
        cin>>temp_cuent;
        cout<<endl;
        pos = BuscarCuent(temp_cuent);
        if(temp_cuent=="*"){  
            cout<<endl;
            cout<<"Regresando al menu anterior"<<endl;
            break;
        }
        if(pos==-2){
            cout<<"cuenta dada de baja, ingrese otra"<<endl;
            i++;
        }else{
            if(pos==-1){
                cout<<"No existe una cuenta con ese usuario, intente de nuevo."<<endl;
                i++;
            }else{
                if(cuent[pos].perm==true){
                    do{
                        i = 0;
                        cout<<"Ingrese la contrasena: ";
                        cin>>temp_con;
                        if(cuent[pos].pass==temp_con){
                            cout<<"\nIngreso exitoso\n"<<endl;
                            i = 10;
                        }else{
                            cout<<"Contrasena incorrecta, ingrese nuevamente";
                            i++;
                        }
                    }while(i<3);
                }else{
                    cout<<"Cuenta sin permisos de administrador, regresando al menu anterior"<<endl;
                    i = 4;
                }
            }
        }
    }while(i<3);

    
	while(op!=8 && i==10){
        cout << endl;
        cout<<"Menu administrador\n"<<endl;
        cout << "1.Altas" << endl;
        cout << "2.Bajas" << endl;
        cout << "3.Consultas" << endl;
        cout << "4.Modificaciones" << endl;
        cout << "5.Mostrar Inventario" << endl;
        cout << "6.Administracion de cuentas de usuario" << endl;
        cout << "7.corte de caja" << endl;
        cout << "8.Regresar al menu anterior" << endl;
        cin >> op;
        switch (op){
	        case 1: Altas ();
	        break;
	        case 2: Bajas ();
	        break;
	        case 3: Consultas ();
	        break;
	        case 4: Modificar ();
	        break;
            case 5: MostrarInventario ();
    	    break;
	        case 6: AdministradorCuentas ();
    	    break;
    	    case 7: Cortedecaja ();
    	    break;
    	    case 8: cout << "Regresando al menu anterior." << endl;
        	break;
    	    default: cout << "Opcion Inexistente." << endl;
	    }
	}
}

void Altas(){  
    int pos, tex, nrt, res;
    double pct, pvt;
    string prod_temp;
    while(true){
        cout<<"Alta de productos"<<endl;
        cout<<"producto: ";
        cin>>prod_temp;
        if(prod_temp=="*"){  
            cout<<endl;
            cout<<"Regresando al menu anterior"<<endl;
            break;
        }
        pos=Buscar(prod_temp);  
        if(pos!=-1){
            if(pos==-2){ 
                cout<<"\nProducto dado de baja"<<endl;
                cout<<"\nQuiere reactivar producto? "<<endl;
                cout<<"1-Si"<<endl<<"2-No";
                cout<<endl<<"opcion: ";
                cin>>res;
                if(res==1){
                    CambiarStProd(prod_temp);
                    cout<<"producto activado."<<endl;
                }
            }else{
                
                cout<<"El producto ya existe, ingresa otro diferente: "<<endl;
            }
        }else{
            product[total].nombre=prod_temp; //agrega producto nuevo
            do{
                cout<<"Ingresa el precio de compra: "<<endl;
                cin>>pct;
                cout<<"Ingresa el precio de venta: "<<endl;
                cin>>pvt;  
                if(pct>pvt)
                    cout<<"El precio de venta es menor que el precio de compra: "<<endl;  
                    else{
                        product[total].pc = pct;
                        product[total].pv = pvt;
                        break;
                    }
            }while(true);
        
            do{  
                cout<<"\nIngrese las existencias del producto: "; //Existencias
                cin>>tex;
                if(tex<=0){
                    cout<<"Ingrese una existencia valida: "<<endl; 
                }else{
                    cout<<"\nIngrese el nivel de reorden: ";
                    cin>>nrt;
                    if(tex<nrt){
                        cout<<"Las existencias son menor que el nivel de reorden. "<<endl;  
                    }else{
                        product[total].nr =nrt;
                        product[total].ex=tex;
                        product[total].st = true;
                        product[total].id = total+1;
                        total++;
                        break;
                    }
                }
            }while(true);   
        }
    }
}

void CambiarStCuent(string cuent_temp){
    int i=0;
        while(cuent_temp!=cuent[i].nombre and i<tlcuentas)
            i++;
        product[i].st=true;
}

void CambiarStProd(string prod_temp){
    int i=0;
        while(prod_temp!=product[i].nombre and i<total)
            i++;
        product[i].st=true;
}

int Buscar(string prod){  
    int i=0;
    while(prod!=product[i].nombre and i<total){
        i++;
    }
        
    if(i==total)
        return -1;
    else
        if(product[i].st==false)
            return -2;
        else
            return i;
    
}

void Bajas (){  
    int pos;
    string prod_temp;
    while(true){
        cout<<"Producto a dar de baja: "<<endl;
        cin>>prod_temp; 
        if(prod_temp=="*"){
            cout<<endl;
            cout<<"Regresando al menu anterior..."<<endl;
            break;
        }
        pos=Buscar(prod_temp);
        if(pos<0) 
            cout<<"Producto previamente dado de baja"<<endl;
        else{
            product[pos].st=false;
            
            cout<<"Producto exitosamente dado de baja"<<endl;
            
        }
    }
}

void Consultas(){   
    string prod_temp;
    int pos;
    while(true){
        cout<<"\nProducto a consultar: ";
        cin>>prod_temp;
        if(prod_temp=="*"){
            cout<<endl;
            cout<<"Regresando al menu anterior..."<<endl;
            break;
        }
        pos=Buscar(prod_temp);
        if(pos==-1)
            cout<<"producto no encontrado o dado de baja"<<endl;
        else{
            cout<<"ID"<<setw(20)<<"Producto"<<setw(20)<<"PC"<<setw(20)<<"Pv"<<setw(20)<<"Existencias"<<setw(20)<<"NR"<<setw(20)<<"Resurtir"<<endl; 
            cout<<product[pos].id<<setw(20)<<product[pos].nombre<<setw(20)<<product[pos].pc<<setw(20)<<product[pos].pv<<setw(20)<<product[pos].ex<<setw(20)<<product[pos].nr;
            if(product[pos].nr>=product[pos].ex){
            cout<<setw(20)<<"*";
            }else{
            cout<<setw(20)<<" ";
            }
        }
    }cout<<endl;
}

void Modificar(){
    string prod;
    int i, op;
    op=0;
    cout<<"Modificaciones"<<endl;
    while(true){
        cout<<"\nIngrese nombre del producto a modificar: ";
        cin>>prod;
        if(prod=="*"){
            cout<<"\n\nRegresando al menu anterior...\n"<<endl;
            op=5;
            break;
        }else{
            i = Buscar(prod);
            if(i<0){
            cout<<"El producto no se encontro";
            }else
                break;
        }
    }
    while(op!=5){
        cout<<"Modificaciones"<<endl;
        cout<<"\n\nID\tProducto\tPC\tPV\tExistencias\tNR"<<endl;
        cout<<"\n"<<product[i].id<<"\t"<<product[i].nombre<<"\t\t";
        cout<<product[i].pc<<"\t"<<product[i].pv<<"\t";
        cout<<product[i].ex<<"\t\t"<<product[i].nr<<endl<<endl;
        cout<<"\n1.-Precio de compra\n2.-Precio de venta\n3.-Existencias\n4.-Nivel de reorden\n5.-Regresar al menu anterior\n"<<endl;
        cin>>op;
        switch (op){
            case 1:
                cout<<"\nIngrese el nuevo precio de compra: ";
                cin>>product[i].pc;
                cout<<"\nPrecio modificado con exito"<<endl;     
                break;
            case 2: 
                cout<<"\nIngrese el nuevo precio de venta: ";
                cin>>product[i].pv;
                cout<<"\nPrecio modificado con exito"<<endl;
                break;
            case 3:
                cout<<"\nIngrese la nueva cantidad de existencias: ";
                cin>>product[i].ex;
                cout<<"\nExistencias modificado con exito"<<endl;
                break;
            case 4:
                cout<<"\nIngrese la nueva cantidad de nivel de reorden: ";
                cin>>product[i].nr;
                cout<<"\nNivel de reorden modificado con exito"<<endl;
                break;
            case 5:
                cout<<"\nRegresando al menu anterior\n\n";
                break;
            default:
                cout<<"\nOpcion invalida\n"<<endl;
                break;
        }
    }
}

void MostrarInventario (){
    int i,op,j;
    int id_ord[sizeof(product)/sizeof(product[0])];
    string prod_ord[sizeof(product)/sizeof(product[0])];
    string temp;
    int int_temp;
    int tamano= sizeof(product)/sizeof(product[0]);
    while(op!=3){
        cout<<"\t\tMostrar inventario"<<endl;
        cout<<"1. Por ID"<<endl;
        cout<<"2. Por Producto"<<endl;
        cout<<"3. Regresar al menu anterior"<<endl;
        cin>>op;
        switch(op){
            case 1:
                cout<<"ID"<<setw(20)<<"Producto"<<setw(20)<<"PC"<<setw(20)<<"PV"<<setw(20)<<"Existencias"<<setw(20)<<"NR"<<setw(20)<<"Resurtir"<<endl;
                for(i=0;i<tamano;i++){
                    id_ord[i]=product[i].id;
                }
                for(i=0;i<tamano;i++){
                    for(j=1;j<tamano-i;j++){
                        if(product[j].st==true){
                            if(id_ord[j-1]>id_ord[j]){
                                int_temp=id_ord[j-1];
                                id_ord[j-1]=id_ord[j];
                                id_ord[j]=int_temp;
                            }
                        }
                    }
                }
                for(i=0;i<tamano;i++){
                    if(product[i].st==true){
                        for(j=0;j<tamano;j++){
                            if(id_ord[i]==product[j].id){
                                if(product[j].st==true){
                                    cout<<product[j].id<<setw(20)<<product[j].nombre<<setw(20)<<product[j].pc<<setw(20)<<product[j].pv<<setw(20)<<product[j].ex<<setw(20)<<product[j].nr;
                                    if(product[j].nr>=product[j].ex){
                                        cout<<setw(20)<<"*";
                                    }else{
                                        cout<<setw(20)<<" ";
                                    }
                                }
                                cout<<endl;
                            }
                        } 
                    }
                }
                break;
            case 2:
                cout<<"ID"<<setw(20)<<"Producto"<<setw(20)<<"PC"<<setw(20)<<"PV"<<setw(20)<<"Existencias"<<setw(20)<<"NR"<<setw(20)<<"Resurtir"<<endl;
                for(i=0;i<tamano;i++){
                    prod_ord[i]=product[i].nombre;
                }
                for(i=0;i<tamano;i++){
                    for(j=1;j<tamano-i;j++){
                        if(product[j].st==true){
                            if(prod_ord[j-1]>prod_ord[j]){
                                temp=prod_ord[j-1];
                                prod_ord[j-1]=prod_ord[j];
                                prod_ord[j]=temp;
                            }
                        }
                    }
                }
                for(i=0;i<tamano;i++){
                    if(product[i].st==true){
                        for(j=0;j<tamano;j++){
                            if(prod_ord[i]==product[j].nombre){
                                if(product[j].st==true){
                                    cout<<product[j].id<<setw(20)<<product[j].nombre<<setw(20)<<product[j].pc<<setw(20)<<product[j].pv<<setw(20)<<product[j].ex<<setw(20)<<product[j].ex;
                                    if(product[j].nr>=product[j].ex){
                                        cout<<setw(20)<<"*";
                                    }else{
                                        cout<<setw(20)<<" ";
                                    }
                                }
                                cout<<endl;
                            }
                        } 
                    }
                }
                break;
            case 3:
                cout<<"\nRegresando al menu anterior\n\n";
                break;
            default:
                cout<<"\nOpcion invalida\n"<<endl;
                break;
        }
    }
}

void AdministradorCuentas(){
   int op;
  do{
    cout<<"Menu Administador Cuentas de Usuarios: " << endl;
    cout<<"1.Altas" << endl;
    cout<<"2.Bajas" << endl;
    cout<<"3.Consultas" << endl;
    cout<<"4.Modificaciones"<<endl;
    cout<<"5.Mostrar cuentas de usuarios"<<endl;
    cout<<"6.Regresar al menu anterior"<<endl;
    cin>>op;
    switch (op){
        case 1: AltaCU ();
        break;
        case 2: BajaCU (); 
        break;
        case 3: ConsultasCU ();
        break;
        case 4: ModiCU ();
        break;
        case 5: MostrarCU ();
        break;
        case 6: cout <<"Regresando al menu anterior";
        break;
	    default: cout << "Opcion invalida" << endl;
	}
  }while (op!=6);
}

void Cortedecaja(){
    char i;
    cout << "Esta opcion todavia no esta implementada" << endl;
    cout << "presione * para volver al menu anterior" << endl;
    cin >> i;
}



void Ventas (){
    int pos;
    int op, i;
    int temp_con;
    string temp_prod;
    string temp_cuent;
    int ventcant;
    i = 0;
    cout<<"Para acceder porfavor ingrese: "<<endl;
    cout<<endl;
    do{
        cout<<"Nombre de Usuario: ";
        cin>>temp_cuent;
        cout<<endl;
        pos = BuscarCuent(temp_cuent);
        if(temp_cuent=="*"){  
            cout<<endl;
            cout<<"Regresando al menu anterior"<<endl;
            break;
        }
        if(pos==-2){
            cout<<"cuenta dada de baja, ingrese otra"<<endl;
            i++;
        }else{
            if(pos==-1){
                cout<<"No existe una cuenta con ese usuario, intente de nuevo."<<endl;
                i++;
            }else{
                if(cuent[pos].perm==false){
                    do{
                        i = 0;
                        cout<<"Ingrese la contrasena: ";
                        cin>>temp_con;
                        if(cuent[pos].pass==temp_con){
                            cout<<"\nIngreso exitoso\n"<<endl;
                            i = 10;
                        }else{
                            cout<<"Contrasena incorrecta, ingrese nuevamente";
                            i++;
                        }
                    }while(i<3);
                }else{
                    cout<<"Cuenta sin permisos de administrador, regresando al menu anterior"<<endl;
                    i = 4;
                }
            }
        }
    }while(i<3);
    int x=0;
int numVenta=0;
do{
    do{ 
        cout<<"producto: "<<endl;
        cin>>temp_prod;
        if(temp_prod=="*"){
            break;
        }
        pos=Buscar(temp_prod);
        if(pos==-1)
            cout<<"Producto inexistente"<<endl;	
        else
            if(pos==-2)
                cout<<"Producto dado de baja"<<endl;
            else{
                ListaVentas[numVenta].Producto[x]=temp_prod;
                cout<<"cantidad"<<endl;
                cin>>ventcant;
                if(product[pos].ex<ventcant){
                    cout<<"No hay  "<<ventcant<<",solo hay "<<product[pos].ex;
                    cout<<"Realizar la venta de: "<<product[pos].ex;
                    cout<<"1. si\n"<<"2. No\n";
                    if(op==1){
                        product[pos].ex=0;
                        ListaVentas[numVenta].cantidad[x]=ventcant;
                        ListaVentas[numVenta].subtotal[x]=ventcant*product[pos].pv;
                        x++;
                    } 
                }else{
                    product[pos].ex=product[pos].ex-ventcant;
                    ListaVentas[numVenta].cantidad[x]=ventcant;
                    ListaVentas[numVenta].subtotal[x]=ventcant*product[pos].pv;
                    x++; 
                }
            } 
    }while(temp_prod!="*");
    numVenta++;
}while(temp_prod!="**");


}




int BuscarCuent(string nom){
    int i = -1;
    while(i<tlcuentas){
        i++;
        if(i == tlcuentas)
            return -1;
        else{
            if(cuent[i].nombre == nom){
                if(cuent[i].st==false)
                    return -2;
                else
                    return i;
            }
            
        }
            
    }
}





void AltaCU(){  
    int pos;
    string cuent_temp;
    int res;
    while(true){
        cout<<"\t\tAlta de Cuentas"<<endl;
        cout<<"Nombre de la nueva cuenta: ";
        cin>>cuent_temp;
        if(cuent_temp=="*"){  
            cout<<endl;
            cout<<"Regresando al menu anterior"<<endl;
            break;
        }
        pos=BuscarCuent(cuent_temp);  
        if(pos!=-1){
            if(pos==-2)
            { 
                cout<<"Cuenta dada de baja"<<endl;
                cout<<"Quiere reactivarla"<<endl;
                cout<<"1. Si"<<endl<<"2. No"<<endl;
                cout<<"opcion: ";
                cin>>res;
                if(res==1){
                    CambiarStCuent(cuent_temp);
                    cout<<"cuenta activada."<<endl;
                }
            }else{
                cout<<"La cuenta ya existe, ingresa otra diferente: "<<endl;
            }
        }else{
            cuent[tlcuentas].nombre=cuent_temp; 
            cout<<"Ingresa la nueva contrasena: "<<endl;
                cin>>cuent[tlcuentas].pass;
            do{
                cout<<"Tipo de cuenta: "<<endl;
                cout<<"\n1.-Admin\n2.-Vendedor"<<endl;
                cin>>res;
                switch(res){
                    case 1: 
                        cuent[tlcuentas].perm=true;
                        break;
                    case 2:
                        cuent[tlcuentas].perm=false;
                        break;
                    default:
                        cout<<"Opcion inexistente"<<endl;
                        break;
                } 
            }while(res!=1 and res!=2); 
            
            cuent[tlcuentas].st=true;
            tlcuentas++;          
        }
    }
}

void BajaCU(){
       int pos;
    string cuent_temp;
    while(true){
        cout<<"Cuenta a dar de baja: "<<endl;
        cin>>cuent_temp; 
        if(cuent_temp=="*"){
            cout<<endl;
            cout<<"Regresando al menu anterior..."<<endl;
            break;
        }
        pos=BuscarCuent(cuent_temp);
        if(pos==-2) 
            cout<<"Cuenta previamente dada de baja"<<endl;
        else{
            if(pos<0)
                cout<<"cuenta inexistente"<<endl;
            else{
            cuent[pos].st=false;
            cout<<"Cuenta exitosamente dada de baja"<<endl;
            }
        }
    }
}

void ConsultasCU(){  
     string cuent_temp;
    int pos;
    while(true){
        cout<<"\nCuenta a consultar: ";
        cin>>cuent_temp;
        if(cuent_temp=="*"){
            cout<<endl;
            cout<<"Regresando al menu anterior..."<<endl;
            break;
        }
        pos=BuscarCuent(cuent_temp);
        if(pos<0)
            cout<<"Cuenta no encontrada o dada de baja"<<endl;
        else{
            cout<<"Usuario"<<setw(20)<<"Pass"<<setw(20)<<"Tipo"<<setw(20)<<"St"<<endl;
            cout<<cuent[pos].nombre<<setw(20)<<cuent[pos].pass<<setw(20);
            if(cuent[pos].perm==true)
                cout<<"1"<<setw(20);
            else 
                cout<<"2"<<setw(20);
            cout<<cuent[pos].st<<endl;
        }cout<<endl;
    }
}


void ModiCU () {
    string temp_cuent;
    int i, op;
    op=0;
    cout<<"Modificaciones"<<endl;
    while(true){
        cout<<"\nIngrese nombre de la cuenta a modificar: ";
        cin>>temp_cuent;
        if(temp_cuent=="*"){
            cout<<"\n\nRegresando al menu anterior...\n"<<endl;
            op=5;
            break;
        }else{
            i = BuscarCuent(temp_cuent);
            if(i<0){
            cout<<"La cuenta no se encontro";
            }else
                break;
        }
    }
    while(op!=5){
        cout<<"\nModificaciones"<<endl;
        cout<<"Usuario"<<setw(20)<<"Pass"<<setw(20)<<"Tipo"<<setw(20)<<"St"<<endl;
        cout<<cuent[i].nombre<<setw(20)<<cuent[i].pass<<setw(20);
        if(cuent[i].perm==true)
            cout<<"1"<<setw(20);
        else 
            cout<<"2"<<setw(20);
        cout<<cuent[i].st<<endl;
        cout<<"\n1.-Usuario\n2.-Pass\n3.-Tipo\n4.-St\n5.-Regresar al menu anterior\n"<<endl;
        cin>>op;
        switch (op){
            case 1:
                cout<<"\nIngrese el nuevo nombre de usuraio: ";
                cin>>cuent[i].nombre;
                cout<<"\nUsuario modificado con exito"<<endl;     
                break;
            case 2: 
                cout<<"\nIngresa la nueva contraseña: ";
                cin>>cuent[i].pass;
                cout<<"\nContraseña modificada con exito"<<endl;
                break;
            case 3:
                if(cuent[i].perm==false)
                    cuent[i].perm=true;
                else
                    cuent[i].perm=false;
                cout<<"\nTipo modificado con exito"<<endl;
                break;
            case 4:
                if(cuent[i].st==false)
                    cuent[i].st=true;
                else
                    cuent[i].st=false;
                cout<<"\nStatus modificado con exito"<<endl;
                break;
            case 5:
                cout<<"\nRegresando al menu anterior\n\n";
                break;
            default:
                cout<<"\nOpcion invalida\n"<<endl;
                break;
        }
    }
}


void MostrarCU () { 
     int i;
    cout<<"\t\tMostrar cuentas de usuario"<<endl;
    cout<<"Usuario"<<setw(20)<<"Pass"<<setw(20)<<"Tipo"<<setw(20)<<"St"<<endl;
    for(i=0;i<total;i++){
        if(cuent[i].st==true){
            cout<<cuent[i].st<<setw(20)<<cuent[i].pass<<setw(20);
            if(cuent[i].perm==true)
                cout<<"1"<<setw(20);
            else 
                cout<<"2"<<setw(20);
                cout<<cuent[i].st<<endl;
        }else{
            cout<<setw(20)<<" ";

        }
        cout<<endl;
    }
}




