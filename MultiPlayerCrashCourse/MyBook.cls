\ProvidesClass{MyBook}[2026/01/15 v0001]
\NeedsTeXFormat{LaTeX2e}
\newcommand{\@baseclass}{ctexbook}

% Set the default options
\PassOptionsToClass{a4paper}{\@baseclass}
\PassOptionsToClass{fontsize=10pt}{\@baseclass}
\PassOptionsToClass{parskip=half}{\@baseclass}
% Pass through any other options to the base class
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{\@baseclass}} 

\ProcessOptions\relax % Process the options

\LoadClass{\@baseclass} % Load the base class


\RequirePackage{geometry}
\geometry{rmargin=2.45cm,lmargin=1.45cm,tmargin=2.45cm,bmargin=2.45cm}

\RequirePackage{amssymb} % Must be loaded before unicode-math
\RequirePackage[force]{filehook} % Fixes an error
\RequirePackage{unicode-math} % Math fonts in xetexorluatex
\RequirePackage{fontspec}
\setromanfont[Scale=1.04]{Libertinus Serif}
\setsansfont[Scale=1]{Libertinus Sans}
\setmathfont{Libertinus Math}



\RequirePackage[dvipsnames]{xcolor}
%定制一些常用颜色
\definecolor{maincolor}{RGB}{0,33,71}        % Oxford Blue
\definecolor{accentcolor}{RGB}{140,45,25}    % Oxford Red
\definecolor{highlightcolor}{RGB}{255,205,0} % Gold accent
\definecolor{codebg}{RGB}{240,240,245}       % Light blue-tinted code background
\definecolor{codefg}{RGB}{30,30,60}          % Dark blue code foreground
\definecolor{softgray}{RGB}{190,190,200}     % Blue-tinted grey
\definecolor{titlepagebg}{RGB}{230,235,245}  % Soft blue background
\definecolor{inlinecodebg}{RGB}{230,235,245} % Slightly richer blue background for inline code
\definecolor{inlinecodefg}{RGB}{110,30,20}   % Oxford red for inline code text (using accent colour)


\RequirePackage{tikz}
\usetikzlibrary{backgrounds,intersections,positioning,fit,shapes,fadings,decorations.pathmorphing,graphs,quotes,angles,calc,through,shadows,shadows.blur,arrows.meta,shapes.geometric, arrows.meta, patterns}

\pgfdeclarelayer{background}
\pgfdeclarelayer{foreground}
\pgfsetlayers{background,main,foreground}

\RequirePackage[explicit]{titlesec}
\RequirePackage[most]{tcolorbox}
\tcbuselibrary{skins,breakable,hooks}

% 定制章节
\newfont{\font@chapnum}{eurb10 scaled 10000} %
\def\chap@image{} % 章背景图片文件名，默认为空
\newcommand{\setchapterimage}[1]{\def\chap@image{#1}}%

\newsavebox{\chap@titlebox}
\titleformat{\chapter}[display]{\Huge\heiti\thispagestyle{empty}}{}{20pt}
{
	\ifx\chap@image\@empty \def\title@color{maincolor}%
	\else \def\title@color{white}%
	\fi
	% 计算背景图高度
	\begin{lrbox}{\chap@titlebox}
		\begin{tcolorbox}[
			enhanced,
			width=\textwidth,
			top=20mm,
			bottom=15mm,
			sharp corners,
			boxrule=0pt,
			left=0pt,
			right=0pt,
			% 使用预计算的不透明度参数
			opacityfill=0,
			opacityback=0,
			interior hidden,
			colback=maincolor,
			% 并排模式
			sidebyside,
			sidebyside align=center,
			sidebyside gap=5mm,
			lefthand width=3cm,
			segmentation hidden,
			]
			% 左侧：章节序号
			\raggedright
			\tcbox[
			enhanced,
			size=small,
			boxrule=0pt,
			colback=maincolor,
			colframe=white,
			coltext=highlightcolor,
			drop fuzzy shadow,
			]{\font@chapnum\thechapter}
			\tcblower
			% 右侧：章节标题
			\raggedright
			\strut \color{\title@color}{#1}
		\end{tcolorbox}
	\end{lrbox}
	\begin{tikzpicture}[remember picture]
		% 1. 绘制 tcolorbox (前景)
		% 这个 node 没有 overlay，所以它会占据空间并决定 tikzpicture 的位置
		\node[inner sep=0pt] (chapbox) {\usebox{\chap@titlebox}};
		% 2. 绘制背景图片 (背景，裁剪到 tcolorbox 高度)
		\ifx\chap@image\@empty
		\else
		\begin{pgfonlayer}{background}
			\begin{scope}[overlay]
				% 从纸张顶端到 chapbox 底部的裁剪区域，水平铺满整页
				\clip (current page.north west) rectangle (current page.east |- chapbox.south);
				\node[inner sep=0pt, anchor=north] at (current page.north) {\includegraphics[width=\paperwidth]{\chap@image}};
			\end{scope}
		\end{pgfonlayer}
		\fi
	\end{tikzpicture}%
}

% 调整章节标题后的间距，避免正文与背景/标题重叠
\titlespacing{\chapter}{0pt}{-40mm}{4ex}

% Section: 模仿章节样式，左侧实心序号盒子，右侧标题
\titleformat{\section}[hang]{\Large\heiti}{%
	\begin{tikzpicture}[baseline=(node.base)]
		\node[
		fill=maincolor,
		%draw=white,
		line width=1pt,
		rounded corners=4pt,
		text=highlightcolor,
		inner sep=2pt,
		font=\bfseries,
		blur shadow
		] (node) {\thesection};
	\end{tikzpicture}%
}{0.5em}{\color{maincolor}#1}
\titlespacing{\section}{0pt}{0.5ex plus 0.2ex minus .2ex}{1ex plus .2ex}


% Subsection: 左侧空心序号盒子，右侧标题
\titleformat{\subsection}[hang]{\rmfamily\large\bfseries}{%
	\begin{tikzpicture}[baseline=(node.base)]
		\node[
		fill=white,
		draw=maincolor!80!black,
		line width=1pt,
		rounded corners=3pt,
		text=maincolor,
		inner sep=2pt,
		font=\bfseries,
		blur shadow
		] (node) {\thesubsection};
	\end{tikzpicture}%
}{0.5em}{\textcolor{maincolor!80!black}{#1}}
\titlespacing{\subsection}{0pt}{0.25ex plus 0.2ex minus .2ex}{1ex plus .2ex}

% ----------------------------脚注样式 ----------------------------
%脚注使用带圈数字
\RequirePackage{footmisc}
%%定义带圈数字命令
\newfontfamily{\nmfont}{circlenumber}[%
	Extension=.otf,Path=./fonts/]

\newcommand{\quan}[1]{{\nmfont \symbol{#1}}}
\newcommand{\kk}[1]{\quan{\numexpr32+#1}}%\kk{<参数范围1-95>}96、97、98、99分别用\quan{196} \quan{197} \quan{199} \quan{201}

%脚注使用带圈数字
\newcommand*\kkctr[1]{%
\protect\kk{\number\numexpr\value{#1}\relax}%
}%
\renewcommand*\thefootnote{\textcolor{black}{\kkctr{footnote}}}

%%无悬挂脚注格式
\renewcommand\@makefntext[1]{\setlength\parindent{2\ccwd}\selectfont\@thefnmark\ #1}%

%修改\part，使其不分页
\def\@endpart{%
\vskip40\p@%
\@afterheading}

% 定制enumerate环境
\RequirePackage{enumitem}
\setlist[enumerate,1]{label=\small\textcolor{maincolor}{\protect\kk{\arabic*}},leftmargin=*,noitemsep}
\setlist[enumerate,2]{label=\textcolor{accentcolor}{\bfseries\alph*.},leftmargin=*,noitemsep}
\setlist[enumerate,3]{label=\textcolor{highlightcolor}{\bfseries\roman*.},leftmargin=*,noitemsep}

\setlist[itemize]{noitemsep}



%\newenvironment{myenum}{\begin{enumerate}[label=\protect\kk{\arabic*}]\small}{\end{enumerate}}%

%页脚
\RequirePackage{fancyhdr}
\pagestyle{fancy}
\let\headrule\relax
\fancyhead[OL]{\textsc{\sffamily\nouppercase\leftmark}}
\fancyhead[OR]{\sffamily\thepage}
\fancyhead[ER]{\textsc{\sffamily\nouppercase\rightmark}}
\fancyhead[EL]{\sffamily\thepage}
\lfoot{}\cfoot{}\rfoot{}


% ----------------------------代码样式 ----------------------------
\RequirePackage{listings}
\renewcommand*{\lstlistingname}{示例}
\renewcommand*{\lstlistingnamestyle}{\bfseries}
% Configure the listings
\definecolor{listingkeywords}{rgb}{0.0, 0.0, 1.0}
\definecolor{listingidentifiers}{rgb}{0, 0, 0}
\definecolor{listingcomments}{rgb}{0.25, 0.5, 0.5}
\definecolor{listingstrings}{rgb}{0.73, 0.13, 0.13}
\definecolor{listingnumbers}{rgb}{0.25, 0.25, 0.25}
% Define a fancy style
\lstnewenvironment{code}[1][]
{
    \lstset{
        language=[11]C++,
        columns=fullflexible,%fixed
        aboveskip=0.7\topskip,
        belowskip=0.7\topskip,
        basicstyle=\ttfamily\small,
        commentstyle=\color{listingcomments}\itshape,
        keywordstyle=\color{listingkeywords}\bfseries,
        numberstyle=\scriptsize\color{listingnumbers}\ttfamily,
        stringstyle=\color{listingstrings},
        identifierstyle=\color{listingidentifiers},
        backgroundcolor=\color{white},
        breakatwhitespace=false,
        breaklines=true,
        captionpos=t,
        keepspaces=true,
        showspaces=false,
        showstringspaces=false,
        showtabs=false,
        %numbers=left,
        %numbersep=1em,
        %frame=lines,
        %frame=l,   
        frame=none,
        framerule=.7pt,
        emph=[2]{override,final},
        emphstyle=[2]{\color{blue}\bfseries},       
        emph=[3]{UPROPERTY,UFUNCTION,UENUM,UCLASS,USTRUCT},
        emphstyle=[3]{\color{orange!70!black}\bfseries},
        emph=[4]{BlueprintType,EditDefaultsOnly,BlueprintReadOnly},
        emphstyle=[4]{\color{cyan!70!blue}},
        tabsize=2,
        numbers=none,
        escapeinside=``,
        captionpos=b,%标题的位置
        #1
    }
}{}

\newcommand{\ci}[1]{
    \lstinline[language=C++,breakatwhitespace=false,breaklines,basicstyle=\ttfamily,identifierstyle=\color{blue!75!black},keywordstyle=\color{blue}\bfseries]{#1}%
}

\newcommand{\cppsign}{$C^{++}$}
\newcommand{\cpp}[1][11]{$C^{++ \mathbf{#1}}$}

% Improved inline code style
\newtcbox{\inlinecode}{
    nobeforeafter,
    colback=inlinecodebg,
    colframe=maincolor,%inlinecodefg!50,
    boxrule=0.1pt,
    arc=1.0mm,
    left=2pt, right=2pt, top=1.5pt, bottom=1.5pt,
    boxsep=0.7pt,
    on line,
    fontupper=\small\ttfamily\color{maincolor},
    enlarge left by=0mm,
    enlarge right by=0mm
}


% ----------------------------一些盒子 ----------------------------
% --- ENHANCED TCOLORBOX STYLES ---
\newtcolorbox{notebox}[1][注意]{
    enhanced, % Use enhanced features
    colback=maincolor!10,
    colframe=maincolor,
    fonttitle=\sffamily\bfseries,
    coltitle=white, % White text on coloured background
    title=#1,
    left=2mm, right=2mm, top=2mm, bottom=2mm,
    arc=1mm,
    breakable % Allow box to break across pages
}

\newtcolorbox{examplebox}[1][示例]{
    enhanced,
    colback=accentcolor!10,
    colframe=accentcolor,
    fonttitle=\sffamily\bfseries,
    coltitle=white,
    title=#1,
    left=2mm, right=2mm, top=2mm, bottom=2mm,
    arc=2mm,
    breakable
}