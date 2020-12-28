# NCNN break
a breakdown of NCNN

## 一

这个tutorial是笔者在自己学习ncnn的过程的一个记录．等于把自己的理解写了出来，如果有差错，还请大家指正．

这个tutorial还没有写完，后面会随着学习的深入，会不定期的更新．

## 二

这个tutorial的每一节，会分为4个section来讲述，分别是：

> - **开始**　
> - **作用**
> - **实现**
> - **代码示例**

**开始**：每一节的开始，说一下当前学习计划．

**作用**：说一下本节要讲的内容的作用．

**实现**：说一下这一节的内容ncnn是如何实现的．

**代码示例**：把这一节的内容中ncnn相关的代码拿出来，写了个例子．

## 三

每一节，为了方便展示，我都会用一些图表来展示，如：



![lession-5](https://github.com/Zhengtq/ncnn_breakdown/blob/main/image/lesson-5.png)

![Mat](https://github.com/Zhengtq/ncnn_breakdown/blob/main/image/Mat.png)

![](https://github.com/Zhengtq/ncnn_breakdown/blob/main/image/tree.png)

| head | pad_x | (head_use)elemsize | elemsize | elemsize | elemsize | pad_y | pad_y... | (x)      |
| :--- | ----- | ------------------ | :------: | -------- | -------- | ----- | -------- | -------- |
| (x)  | (x)   | (channel2)elemsize | elemsize | elemsize | elemsize | pad_y | pad_y... | (x)      |
| (x)  | (x)   | (channel3)elemsize | elemsize | elemsize | elemsize | pad_y | pad_y... | (x)      |
| (x)  | (x)   | (channel4)elemsize | elemsize | elemsize | elemsize | pad_y | pad_y... | pad_z... |

## 四

在每一节的最后，我都会附上对应的示例代码．在使用每一节的示例代码时候，需要自己clone下来，然后自己编译．一个常用的过程如下：

```bash
git clone git@github.com:Zhengtq/ncnn_breakdown.git
cd ncnn_breakdown && cd lesson && cd lesson_1
mkdir build &&cd build
cmake ..
make -j8
./examples/lession_1
```

## 五

Have Fun !

