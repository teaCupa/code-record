# stl_list
陈硕的stl练习demo,阐述了stl_list的基本理念,对其按照stl_list进行了小幅度修改（去掉父类，将iterator类从list类的内部类提升至外部类）
- 使用双向链表
- 明白了子类、父类的构造析构顺序（子类构造前先构造父类，析构时先析构子类，最后析构父类）
- for(auto x : list) 语法糖，调用begin
