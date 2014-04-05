package visitor;

import syntaxtree.*;
import visitor.*;

public class SymbolTreeBuilder implements Visitor {

  SymbolTable table = new SymbolTable();
  SymbolClass currentClass;
  SymbolMethod currentMethod;


  // MainClass m;
  // ClassDeclList cl;
  public void visit(Program n) {
    table.pushScope();
    n.m.accept(this);
    for ( int i = 0; i < n.cl.size(); i++ ) {
        System.out.println();
        n.cl.elementAt(i).accept(this);
    }
  }
  
  // Identifier i1,i2;
  // Statement s;
  public void visit(MainClass n) {
    currentClass = new SymbolClass(n.i1.s);

    table.pushScope();
    table.addSymbol(n.i1.s, n.i1);
    n.i1.accept(this);

    table.addSymbol(n.i2.s, n.i2);
    n.i2.accept(this);
    
    n.s.accept(this);
    System.out.println("\n\nBEFORE END OF MAIN CLASS:\n" + table.toString());

    table.destroyScope();
  }

  // Identifier i;
  // VarDeclList vl;
  // MethodDeclList ml;
  public void visit(ClassDeclSimple n) {
    currentClass = new SymbolClass(n.i.s);

    table.pushScope();
    table.addSymbol(n.i.s, n.i);
    n.i.accept(this);
    for ( int i = 0; i < n.vl.size(); i++ ) {
        n.vl.elementAt(i).accept(this);
        SymbolVariable tempVar = new SymbolVariable(n.vl.elementAt(i).i.s, n.vl.elementAt(i).t);
        currentClass.addVariable(tempVar);
    }
    for ( int i = 0; i < n.ml.size(); i++ ) {
        n.ml.elementAt(i).accept(this);
        MethodDecl tempMethod = n.ml.elementAt(i);
        SymbolMethod tempSym = new SymbolMethod(tempMethod.i.s, tempMethod.t);
        tempSym.addParent(currentClass);

        for ( int j = 0; j < tempMethod.vl.size(); j++ ) {
          tempMethod.vl.elementAt(j).accept(this);
          SymbolVariable tempVar = new SymbolVariable(tempMethod.vl.elementAt(j).i.s, tempMethod.vl.elementAt(j).t);
          tempSym.addParameter(tempVar);
        }
        currentClass.addMethod(tempSym);
    }
    System.out.println("\n\nBEFORE END OF ClassDeclSimple:\n" + table.toString());
    table.destroyScope();
  }
 
  // Identifier i;
  // Identifier j;
  // VarDeclList vl;
  // MethodDeclList ml;
  public void visit(ClassDeclExtends n) {
    currentClass = new SymbolClass(n.i.s);

    table.pushScope();
    table.addSymbol(n.i.s, n.i);
    n.i.accept(this);

    table.addSymbol(n.j.s, n.j);
    n.j.accept(this);
    for ( int i = 0; i < n.vl.size(); i++ ) {
        n.vl.elementAt(i).accept(this);
        SymbolVariable tempVar = new SymbolVariable(n.vl.elementAt(i).i.s, n.vl.elementAt(i).t);
        currentClass.addVariable(tempVar);
    }
    for ( int i = 0; i < n.ml.size(); i++ ) {
        n.ml.elementAt(i).accept(this);
        MethodDecl tempMethod = n.ml.elementAt(i);
        SymbolMethod tempSym = new SymbolMethod(tempMethod.i.s, tempMethod.t);
        tempSym.addParent(currentClass);

        for ( int j = 0; j < tempMethod.vl.size(); j++ ) {
          tempMethod.vl.elementAt(j).accept(this);
          SymbolVariable tempVar = new SymbolVariable(tempMethod.vl.elementAt(j).i.s, tempMethod.vl.elementAt(j).t);
          tempSym.addParameter(tempVar);
        }
        currentClass.addMethod(tempSym);
    }
    System.out.println("\n\nBEFORE END OF ClassDeclSimple:\n" + table.toString());
    table.destroyScope();
  }

  // Type t;
  // Identifier i;
  public void visit(VarDecl n) {
    if (n.t instanceof IdentifierType) {
      IdentifierType steve = (IdentifierType)n.t;
      table.addSymbol(steve.s, steve);
    }

    n.t.accept(this);

    table.addSymbol(n.i.s, n.i);
    n.i.accept(this);
  }

  // Type t;
  // Identifier i;
  // FormalList fl;
  // VarDeclList vl;
  // StatementList sl;
  // Exp e;
  public void visit(MethodDecl n) {
    table.pushScope();
    if (n.t instanceof IdentifierType) {
      IdentifierType steve = (IdentifierType)n.t;
      table.addSymbol(steve.s, steve);
    }
    n.t.accept(this);

    table.addSymbol(n.i.s, n.i);
    n.i.accept(this);
    for ( int i = 0; i < n.fl.size(); i++ ) {
        n.fl.elementAt(i).accept(this);
    }
    for ( int i = 0; i < n.vl.size(); i++ ) {
        n.vl.elementAt(i).accept(this);
    }
    for ( int i = 0; i < n.sl.size(); i++ ) {
        n.sl.elementAt(i).accept(this);
    }
    n.e.accept(this);

    System.out.println("\n\nBEFORE END OF MethodDecl:\n" + table.toString());
    table.destroyScope();
  }

  // Type t;
  // Identifier i;
  public void visit(Formal n) {
    if (n.t instanceof IdentifierType) {
      IdentifierType steve = (IdentifierType)n.t;
      table.addSymbol(steve.s, steve);
    }
    n.t.accept(this);

    table.addSymbol(n.i.s, n.i);
    n.i.accept(this);
  }

  public void visit(IntArrayType n) {
  }

  public void visit(BooleanType n) {
  }

  public void visit(IntegerType n) {
  }

  // String s;
  public void visit(IdentifierType n) {
  }

  // StatementList sl;
  public void visit(Block n) {
    for ( int i = 0; i < n.sl.size(); i++ ) {
        n.sl.elementAt(i).accept(this);
    }
  }

  // Exp e;
  // Statement s1,s2;
  public void visit(If n) {
    n.e.accept(this);
    n.s1.accept(this);
    n.s2.accept(this);
  }

  // Exp e;
  // Statement s;
  public void visit(While n) {
    n.e.accept(this);
    n.s.accept(this);
  }

  // Exp e;
  public void visit(Print n) {
    n.e.accept(this);
  }
  
  // Identifier i;
  // Exp e;
  public void visit(Assign n) {
    table.addSymbol(n.i.s, n.i);
    n.i.accept(this);
    n.e.accept(this);
  }

  // Identifier i;
  // Exp e1,e2;
  public void visit(ArrayAssign n) {
    table.addSymbol(n.i.s, n.i);
    n.i.accept(this);
    n.e1.accept(this);
    n.e2.accept(this);
  }

  // Exp e1,e2;
  public void visit(And n) {
    n.e1.accept(this);
    n.e2.accept(this);
  }

  // Exp e1,e2;
  public void visit(LessThan n) {
    n.e1.accept(this);
    n.e2.accept(this);
  }

  // Exp e1,e2;
  public void visit(Plus n) {
    n.e1.accept(this);
    n.e2.accept(this);
  }

  // Exp e1,e2;
  public void visit(Minus n) {
    n.e1.accept(this);
    n.e2.accept(this);
  }

  // Exp e1,e2;
  public void visit(Times n) {
    n.e1.accept(this);
    n.e2.accept(this);
  }

  // Exp e1,e2;
  public void visit(ArrayLookup n) {
    n.e1.accept(this);
    n.e2.accept(this);
  }

  // Exp e;
  public void visit(ArrayLength n) {
    n.e.accept(this);
  }

  // Exp e;
  // Identifier i;
  // ExpList el;
  public void visit(Call n) {
    n.e.accept(this);
  
    table.addSymbol(n.i.s, n.i);
    n.i.accept(this);
    for ( int i = 0; i < n.el.size(); i++ ) {
        n.el.elementAt(i).accept(this);
    }
  }

  // int i;
  public void visit(IntegerLiteral n) {
  }

  public void visit(True n) {
  }

  public void visit(False n) {
  }

  // String s;
  public void visit(IdentifierExp n) {
    table.addSymbol(n.s, n);
  }

  public void visit(This n) {
  }

  // Exp e;
  public void visit(NewArray n) {
    n.e.accept(this);
  }

  // Identifier i;
  public void visit(NewObject n) {
    table.addSymbol(n.i.s, n.i);
  }

  // Exp e;
  public void visit(Not n) {
    n.e.accept(this);
  }

  // String s;
  public void visit(Identifier n) {
  }
}
