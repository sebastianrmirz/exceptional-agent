class Main {
  public static void main(String args[]) throws Throwable {
    try {
      doIt();
    } catch (Throwable t) {
      System.out.println("Yum! that was a tasty exception I just swallowed");
    }
  }


  public static void doIt() throws Throwable {
    System.out.println("I'm a nasty method, and I will throw an exception. NOW!");
    throw new Throwable();
  }
}
