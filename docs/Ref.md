# 参考

#### liteide 项目结构

─bin
│  ├─bearer
│  ├─iconengines
│  ├─imageformats
│  ├─platforms
│  ├─printsupport
│  ├─styles
│  └─translations
├─lib
│  └─liteide
│      └─plugins
└─share
    └─liteide
        ├─liteapp
        │  ├─kms
        │  ├─mimetype
        │  ├─qrc
        │  │  ├─default
        │  │  │  ├─bookmarks
        │  │  │  │  └─images
        │  │  │  ├─filebrowser
        │  │  │  │  └─images
        │  │  │  ├─golangast
        │  │  │  │  └─images
        │  │  │  ├─golangfmt
        │  │  │  │  └─images
        │  │  │  ├─golangpresent
        │  │  │  │  └─images
        │  │  │  ├─golangtool
        │  │  │  │  └─images
        │  │  │  ├─imageeditor
        │  │  │  │  └─images
        │  │  │  ├─liteapp
        │  │  │  │  └─images
        │  │  │  │      └─logo
        │  │  │  ├─litebuild
        │  │  │  │  └─images
        │  │  │  ├─litedebug
        │  │  │  │  └─images
        │  │  │  ├─liteeditor
        │  │  │  │  └─images
        │  │  │  ├─liteenv
        │  │  │  │  └─images
        │  │  │  └─markdown
        │  │  │      └─images
        │  │  └─gray
        │  │      ├─bookmarks
        │  │      │  └─images
        │  │      ├─filebrowser
        │  │      │  └─images
        │  │      ├─golangast
        │  │      │  └─images
        │  │      ├─golangfmt
        │  │      │  └─images
        │  │      ├─golangpresent
        │  │      │  └─images
        │  │      ├─golangtool
        │  │      │  └─images
        │  │      ├─imageeditor
        │  │      │  └─images
        │  │      ├─liteapp
        │  │      │  └─images
        │  │      │      └─logo
        │  │      ├─litebuild
        │  │      │  └─images
        │  │      ├─litedebug
        │  │      │  └─images
        │  │      ├─liteeditor
        │  │      │  └─images
        │  │      ├─liteenv
        │  │      │  └─images
        │  │      └─markdown
        │  │          └─images
        │  ├─qss
        │  └─template
        │      ├─empty
        │      ├─goarticle
        │      ├─gocmd
        │      ├─gocmdex
        │      ├─gopkg
        │      ├─gopkgex
        │      ├─goslide
        │      ├─gosrc
        │      ├─luasrc
        │      └─mdsrc
        ├─litebuild
        │  └─command
        ├─liteeditor
        │  ├─color
        │  └─kate
        ├─liteenv
        ├─packages
        │  ├─go
        │  │  └─godoc
        │  ├─gopresent
        │  │  ├─js
        │  │  └─static
        │  ├─lua
        │  └─markdown
        │      └─css
        ├─translations
        └─welcome
            ├─css
            ├─en
            ├─images
            └─zh_CN

#### Export_qrc.cmd

执行 src/tools/exportqrc/main.go， 将qrc目录拷贝到liteidex/deploy/liteapp.