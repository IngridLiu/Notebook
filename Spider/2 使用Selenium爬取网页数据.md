# 使用Selenium爬取网页数据

<br>
<br>
<br>
<br>

## 1 Selenium

### 1.1 Selenium介绍

&emsp;&emsp;Selenium 是什么？一句话，自动化测试工具。它支持各种浏览器，包括 Chrome，Safari，Firefox 等主流界面式浏览器，如果你在这些浏览器里面安装一个 Selenium 的插件，那么便可以方便地实现Web界面的测试。换句话说叫 Selenium 支持这些浏览器驱动。Selenium支持多种语言开发，比如 Java，C，Ruby等等，而对于Python，当然也是支持的！

### 1.2 Selenium安装

&emsp;&emsp;

### 1.3 Selenium基础

&emsp;&emsp;详细内容可查看官网文档：http://selenium-python.readthedocs.io/index.html

#### 1.3.1 尝试使用

&emsp;&emsp;我们先来一个小例子感受一下 Selenium，这里我们用 Chrome 浏览器来测试。

```
from selenium import webdriver

browser = webdriver.Chrome()
browser.get('http://www.baidu.com/')

```
&emsp;&emsp;运行这段代码，会自动打开浏览器，然后访问百度。

&emsp;&emsp;如果程序执行错误，浏览器没有打开，那么应该是没有装 Chrome 浏览器或者 Chrome 驱动没有配置在环境变量里。下载驱动，然后将驱动文件路径配置在环境变量即可。

&emsp;&emsp;驱动下载地址：https://sites.google.com/a/chromium.org/chromedriver/downloads

&emsp;&emsp;Linux的环境变量也好设置，在~/.bashrc文件中export即可，记得source ~/.bashrc。

&emsp;&emsp;当然，你不设置环境变量也是可以的，程序可以这样写：

```
from selenium import webdriver

browser = webdriver.Chrome('path\to\your\chromedriver.exe')
browser.get('http://www.baidu.com/')


```

&emsp;&emsp;上面的path\to\your\chromedriver.exe 是你的chrome驱动文件位置，可以使用绝对路径。我们通过驱动的位置传递参数，也可以调用驱动，

#### 1.3.2 模拟提交

&emsp;&emsp;下面的代码实现了模拟提交提交搜索的功能，首先等页面加载完成，然后输入到搜索框文本，点击提交，然后使用page_source打印提交后的页面的信息。

```
from selenium import webdriver
from selenium.webdriver.common.keys import Keys

driver = webdriver.Chrome()
driver.get("http://www.python.org")
assert "Python" in driver.title
elem = driver.find_element_by_name("q")
elem.send_keys("pycon")
elem.send_keys(Keys.RETURN)
print(driver.page_source)

```
&emsp;&emsp;其中 driver.get 方法会打开请求的URL，WebDriver 会等待页面完全加载完成之后才会返回，即程序会等待页面的所有内容加载完成，JS渲染完毕之后才继续往下执行。注意：如果这里用到了特别多的 Ajax 的话，程序可能不知道是否已经完全加载完毕。

&emsp;&emsp;WebDriver 提供了许多寻找网页元素的方法，譬如 find_element_by_* 的方法。例如一个输入框可以通过 find_element_by_name 方法寻找 name 属性来确定。

&emsp;&emsp;然后我们输入来文本然后模拟点击了回车，就像我们敲击键盘一样。我们可以利用 Keys 这个类来模拟键盘输入。

&emsp;&emsp;最后最重要的一点是可以获取网页渲染后的源代码。通过，输出 page_source 属性即可。这样，我们就可以做到网页的动态爬取了。

#### 1.3.3 元素选取

&emsp;&emsp;关于元素的选取，有如下API：

&emsp;&emsp;单个元素选取：

```
find_element_by_id
find_element_by_name
find_element_by_xpath
find_element_by_link_text
find_element_by_partial_link_text
find_element_by_tag_name
find_element_by_class_name
find_element_by_css_selector

```

&emsp;&emsp;多个元素选取：

```
find_elements_by_name
find_elements_by_xpath
find_elements_by_link_text
find_elements_by_partial_link_text
find_elements_by_tag_name
find_elements_by_class_name
find_elements_by_css_selector

```

&emsp;&emsp;另外还可以利用 By 类来确定哪种选择方式：

```
from selenium.webdriver.common.by import By

driver.find_element(By.XPATH, '//button[text()="Some text"]')
driver.find_elements(By.XPATH, '//button')

```

&emsp;&emsp;By类的一些属性如下：

```
ID = "id"
XPATH = "xpath"
LINK_TEXT = "link text"
PARTIAL_LINK_TEXT = "partial link text"
NAME = "name"
TAG_NAME = "tag name"
CLASS_NAME = "class name"
CSS_SELECTOR = "css selector"

```

&emsp;&emsp;这些方法跟JavaScript的一些方法有相似之处，find_element_by_id，就是根据标签的id属性查找元素，find_element_by_name，就是根据标签的name属性查找元素。举个简单的例子，比如我想找到下面这个元素：

```
<input type="text" name="passwd" id="passwd-id" />

```

&emsp;&emsp;我们可以这样获取它：

```
element = driver.find_element_by_id("passwd-id")
element = driver.find_element_by_name("passwd")
element = driver.find_elements_by_tag_name("input")
element = driver.find_element_by_xpath("//input[@id='passwd-id']")

```

&emsp;&emsp;前三个都很好理解，最后一个xpath什么意思？这个无需着急，xpath是非常强大的元素查找方式，使用这种方法几乎可以定位到页面上的任意元素，在后面我会进行单独讲解。

#### 1.3.4 界面交互

&emsp;&emsp;通过元素选取，我们能够找到元素的位置，我们可以根据这个元素的位置进行相应的事件操作，例如输入文本框内容、鼠标单击、填充表单、元素拖拽等等。由于篇幅原因，我就不一一讲解了，主要讲解本次实战用到的鼠标单击，更详细的内容，可以查看官方文档。

```
elem = driver.find_element_by_xpath("//a[@data-fun='next']")
elem.click()

```

&emsp;&emsp;比如上面这句话，我使用find_element_by_xpath()找到元素位置，暂且不用理会这句话什么意思，暂且理解为找到了一个按键的位置。然后我们使用click()方法，就可以触发鼠标左键单击事件。是不是很简单？但是有一点需要注意，就是在点击的时候，元素不能有遮挡。什么意思？就是说我在点击这个按键之前，窗口最好移动到那里，因为如果这个按键被其他元素遮挡，click()就触发异常。因此稳妥起见，在触发鼠标左键单击事件之前，滑动窗口，移动到按键上方的一个元素位置：
 
```
page = driver.find_elements_by_xpath("//div[@class='page']")
driver.execute_script('arguments[0].scrollIntoView();', page[-1]) #拖动到可见的元素去

```

&emsp;&emsp;上面的代码，就是将窗口滑动到page这个位置，在这个位置，我们能够看到我们需要点击的按键。

#### 1.3.5 添加User-Agent

&emsp;&emsp;使用webdriver，是可以更改User-Agent的，代码如下

```
from selenium import webdriver

options = webdriver.ChromeOptions()
options.add_argument('user-agent="Mozilla/5.0 (Linux; Android 4.0.4; Galaxy Nexus Build/IMM76B) AppleWebKit/535.19 (KHTML, like Gecko) Chrome/18.0.1025.133 Mobile Safari/535.19"')
driver = webdriver.Chrome(chrome_options=options)
driver.get('https://www.baidu.com/')

```

&emsp;&emsp;使用Android的User-Agent打开浏览器，画风是这样的(第二条新闻的图片略劲爆)：


<br>


## 2 实例

&emsp;&emsp;现在我们来看一个爬取某网站美元人民币历史汇率信息的数据的代码：

```

def exchage_rate_spider(url):

    print("start to crawl " + url )

    # 使用selenium模拟获取数据的流程，找到抓取数据的页面
    driver = webdriver.Chrome(chromedriver_path)
    driver.implicitly_wait(10)
    driver.get(url)
    elem = driver.find_element_by_id("widgetFieldDateRange")
    elem.click()

    elem_start_date = driver.find_element_by_id("startDate")
    elem_start_date.clear()
    elem_start_date.send_keys("2014/01/01")

    elem_end_date = driver.find_element_by_id("endDate")
    elem_end_date.clear()
    elem_end_date.send_keys(datetime.now().strftime("%Y/%m/%d"))

    elem_in = driver.find_element_by_id("applyBtn")
    elem_in.click()

    #data_table = driver.find_element_by_id("results_box")
    data_table = driver.find_element_by_id("curr_table")
    data_lines = data_table.text.split("\n")
    exchange_rate = []
    for data_line in data_lines:
        data_items = data_line.split(" ")
        data = []
        for i in range(len(data_items)-1):
            data.append(data_items[i])
        exchange_rate.append(data)

    return exchange_rate
    
    
    
    
if __name_ == "main":
    
    url = https://cn.investing.com/currencies/usd-cny-historical-data
    usd_exchange_rate = exchage_rate_spider(url)


```

<br>
<br>
<br>
<br>
<br>
<br>

## Reference:

1.[Python3网络爬虫(九)：使用Selenium爬取百度文库word文章](https://blog.csdn.net/c406495762/article/details/72331737)
