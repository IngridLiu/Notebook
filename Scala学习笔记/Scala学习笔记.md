# Scala学习笔记

<br>
<br>
<br>
<br>

### 1 Scala入门

#### scala Hello World
```scala
//HelloWorld.scala
object HelloWorld {
    def main(args: Array[String]): Unit = {
        println("Hello, world!")
    }
}

//run
scalac HelloWorld.scala //编译
scala HelloWorld.scala  //运行
```

<br>
<br>

### Scala变量

#### Scala变量

```scala
var myVar : String = 'Ingr' //声明变量myVar
val myVal : String = 'Ingr' //声明常量myVal

var myVar = 10; //在 Scala 中声明变量和常量不一定要指明数据类型，在没有指明数据类型的情况下，其数据类型是通过变量或常量的初始值推断出来的。所以，如果在没有指明数据类型的情况下声明变量或常量必须要给出其初始值，否则将会报错。

val xmax, ymax = 100  // Scala 支持多个变量的声明,xmax, ymax都声明为100
val ps = (40, "Foo")    //pa: (Int, String) = (40,Foo),如果方法返回值是元组，我们可以使用 val 来声明一个元组。
```

<br>

#### Scala字符串
```scala
var greeting:String = "Hello World!"    //创建字符串
var greeting = "Hello World!"   //不一定为字符串指定String类型，因为Scala编译器会自动推断出字符串的类型为String。

printf("浮点型变量为 " + "%f, 整型变量为 %d, 字符串为 " + " %s", floatVar, intVar, stringVar)  //字符串格式化输出

str.length()   //获取str字符串的长度
str.format()   //格式化字符串
str.split(String regex, int limit)) //根据匹配给定的正则表达式来拆分此字符串
str_1.concat(str_2) //使用concat()方法连接两个字符串

```

<br>

#### Scala数组

```scala
// 数组声明
var z:Array[String] = new Array[String](3)  // z 声明一个字符串类型的数组，数组长度为 3 ，可存储 3 个元素。
var z = new Array[string](3)
var myMatrix = ofDim[Int](3,3)  // 声明一个二维数组

//数组创建
z(0) = "Runoob"; z(1) = "Baidu"; z(4/2) = "Google"  //先声明z，再给z的每一个index赋值
var z = Array("Runoob", "Baidu", "Google")  //直接通过赋值创建字符串
list = range(10, 20, 2) //使用了 range() 方法来生成一个区间范围内的数组

//遍历数组
for( i <- 1 to (myList.length - 1) ) {
         if (myList(i) > max) max = myList(i);
}

//数组合并
list_3 = concat(list_1, list_2)
```

#### scala List

&emsp;&emsp;Scala 列表类似于数组，它们所有元素的类型都相同，但是它们也有所不同：列表是不可变的，值一旦被定义了就不能改变，其次列表具有递归的结构（也就是链接表结构）而数组不是。。

&emsp;&emsp;列表的元素类型 T 可以写成 List[T]。例如，以下列出了多种类型的列表：

```scala
// 创建List
val x = List(1,2,3,4)   //定义整型List
val site: List[String] = List("Runoob", "Google", "Baidu")   //创建字符串List
val empty: List[Nothing] = List()
val dim: List[List[Int]] = List(List(1, 0, 0), List(0, 1, 0), List(0, 0, 1))

val site = List.fill(3)("Runoob")   //重复Runoob 3次;List.fill()方法创建一个指定重复数量的元素列表，第一个参数为重复次数，第二个元素为重复的元素。
val squares = List.tabulate(6)(n => n * n)  //通过给定的函数创建 5 个元素;List.tabulate() 方法是通过给定的函数来创建列表。方法的第一个参数为元素的数量，可以是二维的，第二个参数为指定的函数，我们通过指定的函数计算结果并返回值插入到列表中，起始值为 0。

//创建List
val nums = 1 :: (2 :: (3 :: (4 :: Nil)))//创建列表的两个基本单位是Nil和::
val site = "Runoob" :: ("Google" :: ("Baidu::Nil")) 
val empty = Nil //Nil也可以表示为一个空列表
val dim = (1 :: (0 :: (0 :: Nil))) :: (0 :: (1 :: (0 :: Nil))) :: (0 :: (0 :: (1 :: Nil))) :: Nil

site.head   //返回site list的第一个元素
site.tail   //返回一个list，包含了site list除了第一元素之外的其他元素
site.isEmpty    //在list为空时返回true
site.reverse    //

list_3 = list_1 ::: list_2  //合并list
list_3 = list_1.:::(list_2) //合并list
list_3 = List.concat(list_1, list_2)    //合并list,将列表的顺序反转;
```

### scala 元组

&emsp;&emsp;与列表一样，元组也是不可变的，但与列表不同的是元组可以包含不同类型的元素。

&emsp;&emsp;元组的值是通过将单个的值包含在圆括号中构成的。

```scala
// 元组的创建
val t = (1, 3,14, "Fred")
val t = new Tuple(1, 3,14, "Fred")

t._1    //使用 t._1 访问第一个元素， t._2 访问第二个元素
t.productIterator.foreach{ i =>println("Value = " + i )}    //使用 Tuple.productIterator() 方法来迭代输出元组的所有元素

t.toString()    //使用 Tuple.toString() 方法将元组的所有元素组合成一个字符串
t.swap()    // 使用 Tuple.swap 方法来交换元组的元素
```

<br>

#### scala Set

&emsp;&emsp;Scala Set(集合)是没有重复的对象集合，所有的元素都是唯一的。

&emsp;&emsp;Scala 集合分为可变的和不可变的集合。默认情况下，Scala 使用的是不可变集合，如果你想使用可变集合，需要引用 scala.collection.mutable.Set 包。

```scala
import scala.collection.mutable.Set // 可以在任何地方引入可变集合

val mutableSet = Set(1,2,3)

mutable += 5    //mutableSet每个元素+5
mutableSet.add(4)   //mutableSet添加元素4;虽然可变Set和不可变Set都有添加或删除元素的操作，但是有一个非常大的差别。对不可变Set进行操作，会产生一个新的set，原来的set并没有改变，这与List一样。 而对可变Set进行操作，改变的是该Set本身，与ListBuffer类似。
mutableSet.remove(4)    //mutableSet去除元素
mutableSet.head    // 返回集合第一个元素
mutableSet.tail    //  返回一个集合，包含除了第一元素之外的其他元素
mutableSet.isEmpty //  在集合为空时返回true
mutableSet.min  // 使用 Set.min 方法来查找集合中的最小元素
mutableSet.max  //  使用 Set.max 方法查找集合中的最大元素

set_3 = set_1 + set_2   //连接两个集合
set_3 = set_1.++(set_2) //连接两个集合

set_3 = set_1.&(set_2)  //使用 Set.& 方法来查看两个集合的交集元素。
set_3 = set_1.intersect(set_2)  // 使用Set.intersect 方法来查看两个集合的交集元素。
```

#### scala Map

&emsp;&emsp;Map(映射)是一种可迭代的键值对（key/value）结构。

&emsp;&emsp;所有的值都可以通过键来获取。

&emsp;&emsp;Map 中的键都是唯一的。

&emsp;&emsp;Map 也叫哈希表（Hash tables）。

&emsp;&emsp;Map 有两种类型，可变与不可变，区别在于可变对象可以修改它，而不可变对象不可以。

&emsp;&emsp;默认情况下 Scala 使用不可变 Map。如果你需要使用可变集合，你需要显式的引入 import scala.collection.mutable.Map 类

&emsp;&emsp;在 Scala 中 你可以同时使用可变与不可变 Map，不可变的直接使用 Map，可变的使用 mutable.Map。

```scala
//创建Map
var A:Map[Char,Int] = Map() // 空哈希表，键为字符串，值为整型
val colors = Map("red" -> "#FF0000", "azure" -> "#F0FFFF")  // Map 键值对演示
A += ('I' -> 1) //Map中添加 key-value 对

A.keys  //返回 Map 所有的键(key)
A.values  //返回 Map 所有的值(value)
A.isEmpty //在 Map 为空时返回true
A.contains()    //使用 Map.contains 方法来查看 Map 中是否存在指定的 Key

map_3 = map_1 ++ map_2
map_3 = map_1.++(map_2)

// map的遍历
// foreach 循环输出 Map 中的 keys 和 values
sites.keys.foreach{ i =>  
                     print( "Key = " + i )
                     println(" Value = " + sites(i) )}
```

#### scala Option

&emsp;&emsp;Scala Option(选项)类型用来表示一个值是可选的（有值或无值)。

&emsp;&emsp;Option[T] 是一个类型为 T 的可选值的容器： 如果值存在， Option[T] 就是一个 Some[T] ，如果不存在， Option[T] 就是对象 None 。

&emsp;&emsp;Option 有两个子类别，一个是 Some，一个是 None，当他回传 Some 的时候，代表这个函式成功地给了你一个 String，而你可以透过 get() 这个函式拿到那个 String，如果他返回的是 None，则代表没有字符串可以给你。

```scala
// Option的定义
val myMap: Map[String, String] = Map("key1" -> "value")
val option_1: Option[String] = myMap.get("key1")
val option_2: Option[String] = myMap.get("key2")
println(option_1) // Some("value1")
println(option_2) // None

option_1.getOrElse()    //使用 getOrElse()方法来获取元组中存在的元素或者使用其默认的值
option_1.isEmpty()  //使用 isEmpty() 方法来检测元组中的元素是否为 None
```

<br>

#### Scala Iterator（迭代器）

&emsp;&emsp;Scala Iterator（迭代器）不是一个集合，它是一种用于访问集合的方法。

&emsp;&emsp;迭代器 it 的两个基本操作是 next 和 hasNext。

&emsp;&emsp;调用 it.next() 会返回迭代器的下一个元素，并且更新迭代器的状态。

&emsp;&emsp;调用 it.hasNext() 用于检测集合中是否还有元素。

&emsp;&emsp;让迭代器 it 逐个返回所有元素最简单的方法是使用 while 循环：

```scala
val it = Iterator("Baidu", "Google", "Runoob", "Taobao")
      
while (it.hasNext){
    println(it.next())
}

it.max  // 从迭代器it中查找最大元素
it.min  // 从迭代器中查找最小元素
it.size // 查看迭代器中的元素个数
it.length   //查看迭代器中的元素个数

```
<br>

### 3 Scala语句

#### if else语句

```scala
if(布尔表达式){
   if(){
      //嵌套模块
      ***
   }
}else if(){
    ***
}else {
    ***
}
```

#### 循环语句

```scala
// while 循环
while(condition)
{
   statement(s);
}

// do ... while 循环
do {
   statement(s);
} while( condition );

//for循环

//Range 可以是一个数字区间表示 i to j ，或者 i until j。左箭头 <- 用于为变量 x 赋值。
for( var x <- Range ){
   statement(s);
}

// 在 for 循环 中你可以使用分号 (;) 来设置多个区间，它将迭代给定区间所有的可能值。
for( a <- 1 to 3; b <- 1 to 3){
    println( "Value of a: " + a );
    println( "Value of b: " + b );
    
//for 循环集合
for( var x <- List ){
   statement(s);
}
val numList = List(1,2,3,4,5,6);
for( a <- numList ){
    println( "Value of a: " + a );
    
//for 循环过滤
//Scala 可以使用一个或多个 if 语句来过滤一些元素。使用分号(;)来为表达式添加一个或多个的过滤条件。
for( var x <- List
      if condition1; if condition2...
   ){
   statement(s);
  
//for 使用 yield
//可以将 for 循环的返回值作为一个变量存储，注意大括号中用于保存变量和条件，retVal 是变量， 循环中的 yield 会把当前的元素记下来，保存在集合中，循环结束后将返回该集合。
var retVal = for{ var x <- List
     if condition1; if condition2...
}yield x

```

#### Scala 方法与函数

&emsp;&emsp;Scala 有方法与函数，二者在语义上的区别很小。Scala 方法是类的一部分，而函数是一个对象可以赋值给一个变量。换句话来说在类中定义的函数即是方法。

&emsp;&emsp;Scala 中的方法跟 Java 的类似，方法是组成类的一部分。

&emsp;&emsp;Scala 中的函数则是一个完整的对象，Scala 中的函数其实就是继承了 Trait 的类的对象。

&emsp;&emsp;Scala 中使用 val 语句可以定义函数，def 语句定义方法。

```scala
class Test{
    def m(x:Int) = x + 3
    val f = (x:Int) => x + 3
}

// 方法声明
def functionName([参数列表]):[return type]  

// 方法定义
def functionName([参数列表]):[return type] = {
    function body
    return [expr]
}
//如果你不写等于号和方法主体，那么方法会被隐式声明为抽象(abstract)，包含它的类型于是也是一个抽象类型。
//return type 可以是任意合法的 Scala 数据类型。参数列表中的参数可以使用逗号分隔。
//如果方法没有返回值，可以返回为 Unit，这个类似于 Java 的 void, 实例如下：

// 方法调用
functionName(参数列表)  //调用方法的标准格式
[instance.]functionName( 参数列表 ) //如果方法使用了实例的对象来调用，我们可以使用类似java的格式 (使用 . 号)；
```

<br>

#### Scala 闭包

&emsp;&emsp;闭包是一个函数，返回值依赖于声明在函数外部的一个或多个变量。

&emsp;&emsp;闭包通常来讲可以简单的认为是可以访问一个函数里面局部变量的另外一个函数。

```scala
val multiplier = (i:Int) => i * 10  // 函数体内有一个变量 i，它作为函数的一个参数。
val multiplier = (i:Int) => i * factor  //在 multiplier 中有两个变量：i 和 factor。其中的一个 i 是函数的形式参数，在 multiplier 函数被调用时，i 被赋予一个新的值。然而，factor不是形式参数，而是自由变量;
```

<br>
<br>

### 4 Scala 类和对象

&emsp;&emsp;类是对象的抽象，而对象是类的具体实例。类是抽象的，不占用内存，而对象是具体的，占用存储空间。类是用于创建对象的蓝图，它是一个定义包括在特定类型的对象中的方法和变量的软件模板。

&emsp;&emsp;我们可以使用 new 关键字来创建类的对象，实例如下：

```scala
import java.io._

class Point(xc: Int, yc: Int) {
   var x: Int = xc
   var y: Int = yc

   def move(dx: Int, dy: Int) {
      x = x + dx
      y = y + dy
      println ("x 的坐标点: " + x);
      println ("y 的坐标点: " + y);
   }
}

object Test {
   def main(args: Array[String]) {
      val pt = new Point(10, 20);

      // 移到一个新的位置
      pt.move(10, 10);
   }
}
```

#### 4.1 Scala 继承

&emsp;&emsp;Scala继承一个基类跟Java很相似, 但我们需要注意以下几点：

&emsp;&emsp;1、重写一个非抽象方法必须使用override修饰符。

&emsp;&emsp;2、只有主构造函数才可以往基类的构造函数里写参数。

&emsp;&emsp;3、在子类中重写超类的抽象方法时，你不需要使用override关键字。

```scala
import java.io._

class Point(val xc: Int, val yc: Int) {
   var x: Int = xc
   var y: Int = yc
   def move(dx: Int, dy: Int) {
      x = x + dx
      y = y + dy
      println ("x 的坐标点 : " + x);
      println ("y 的坐标点 : " + y);
   }
}

class Location(override val xc: Int, override val yc: Int,
   val zc :Int) extends Point(xc, yc){
   var z: Int = zc

   def move(dx: Int, dy: Int, dz: Int) {
      x = x + dx
      y = y + dy
      z = z + dz
      println ("x 的坐标点 : " + x);
      println ("y 的坐标点 : " + y);
      println ("z 的坐标点 : " + z);
   }
}

object Test {
   def main(args: Array[String]) {
      val loc = new Location(10, 20, 15);

      // 移到一个新的位置
      loc.move(10, 10, 5);
   }
}

```

#### 4.2 Scala 单例对象

&emsp;&emsp;在 Scala 中，是没有 static 这个东西的，但是它也为我们提供了单例模式的实现方法，那就是使用关键字 object。

&emsp;&emsp;Scala 中使用单例模式时，除了定义的类之外，还要定义一个同名的 object 对象，它和类的区别是，object对象不能带参数。

&emsp;&emsp;当单例对象与某个类共享同一个名称时，他被称作是这个类的伴生对象：companion object。你必须在同一个源文件里定义类和它的伴生对象。类被称为是这个单例对象的伴生类：companion class。类和它的伴生对象可以互相访问其私有成员。

&emsp;&emsp;单例对象实例:

```scala
import java.io._

class Point(val xc: Int, val yc: Int) {
   var x: Int = xc
   var y: Int = yc
   def move(dx: Int, dy: Int) {
      x = x + dx
      y = y + dy
   }
}

object Test {
   def main(args: Array[String]) {
      val point = new Point(10, 20)
      printPoint

      def printPoint{
         println ("x 的坐标点 : " + point.x);
         println ("y 的坐标点 : " + point.y);
      }
   }
}
```

&emsp;&emsp;伴生对象实例：

```scala
/* 文件名：Marker.scala
 * author:菜鸟教程
 * url:www.runoob.com
 */

// 私有构造方法
class Marker private(val color:String) {

  println("创建" + this)
  
  override def toString(): String = "颜色标记："+ color
  
}

// 伴生对象，与类共享名字，可以访问类的私有属性和方法
object Marker{
  
    private val markers: Map[String, Marker] = Map(
      "red" -> new Marker("red"),
      "blue" -> new Marker("blue"),
      "green" -> new Marker("green")
    )
    
    def apply(color:String) = {
      if(markers.contains(color)) markers(color) else null
    }
  
    
    def getMarker(color:String) = { 
      if(markers.contains(color)) markers(color) else null
    }
    def main(args: Array[String]) { 
        println(Marker("red"))  
        // 单例函数调用，省略了.(点)符号  
        println(Marker getMarker "blue")  
    }
}
```

<br>
<br>

### 5 Scala Trait(特征)

&emsp;&emsp;Scala Trait(特征) 相当于 Java 的接口，实际上它比接口还功能强大。

&emsp;&emsp;与接口不同的是，它还可以定义属性和方法的实现。

&emsp;&emsp;一般情况下Scala的类只能够继承单一父类，但是如果是 Trait(特征) 的话就可以继承多个，从结果来看就是实现了多重继承。

&emsp;&emsp;Trait(特征) 定义的方式与类类似，但它使用的关键字是 trait

```scala
/* 文件名：Test.scala
 * author:菜鸟教程
 * url:www.runoob.com
 */
trait Equal {
  def isEqual(x: Any): Boolean
  def isNotEqual(x: Any): Boolean = !isEqual(x)
}

class Point(xc: Int, yc: Int) extends Equal {
  var x: Int = xc
  var y: Int = yc
  def isEqual(obj: Any) =
    obj.isInstanceOf[Point] &&
    obj.asInstanceOf[Point].x == x
}

object Test {
   def main(args: Array[String]) {
      val p1 = new Point(2, 3)
      val p2 = new Point(2, 4)
      val p3 = new Point(3, 3)

      println(p1.isNotEqual(p2))
      println(p1.isNotEqual(p3))
      println(p1.isNotEqual(2))
   }
}
```

#### 特征构造顺序

&emsp;&emsp;特征也可以有构造器，由字段的初始化和其他特征体中的语句构成。这些语句在任何混入该特征的对象在构造时都会被执行。

&emsp;&emsp;构造器的执行顺序：

&emsp;&emsp;调用超类的构造器；

&emsp;&emsp;特征构造器在超类构造器之后、类构造器之前执行；

&emsp;&emsp;特征由左到右被构造；

&emsp;&emsp;每个特征当中，父特征先被构造；

&emsp;&emsp;如果多个特征共有一个父特征，父特征不会被重复构造

&emsp;&emsp;所有特征被构造完毕，子类被构造。

&emsp;&emsp;构造器的顺序是类的线性化的反向。线性化是描述某个类型的所有超类型的一种技术规格。


### Scala 文件IO

```scala
//写入文件
val writer = new PrintWriter(new File("test.txt" ))
writer.write("菜鸟教程")
writer.close()

//读取文件
Source.fromFile("test.txt" ).foreach{ 
    print 
}

//读取屏幕输入
val line = StdIn.readLine() 
```

## Reference

1. [Scala 教程](http://www.runoob.com/scala/scala-tutorial.html)

