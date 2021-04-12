syntax on
set t_Co=256
colorscheme gruvbox
"colorscheme molokai
"colorscheme jellybeans
set cursorline
set cursorcolumn
set encoding=utf-8
"顯示行號
set number
"顯示對應行號
set relativenumber
"顯示目前行列
"set ruler
"顯示目前mode
set showmode
"顯示目前指令
set showcmd
"保留個人設定的語法 Highlight
syntax enable
syntax on
"冒號表示同時，逗號表示依序分開
set wildmode=longest:list,full
"自動對齊縮排，follow 上一行的 tab 寬度
set autoindent
"若 shiftwidth=8，tabstop=4
set smarttab
set shiftwidth=4
set tabstop=4
"顯示前行數
set cursorline
"單獨顯示對應誇號 還有時間
set showmatch
set matchtime=1
"Search 後，highlight 所有匹配字 且自動跳目標
set hlsearch
set incsearch
"背景黑色
set background=dark
"設定不可見字元符號
"set listchars=eol:e,tab:<-,trail:.
set listchars=eol:\←,tab:\|-,trail:.,extends:?,precedes:<
set list
set showcmd
set nobackup
set noswapfile
xnoremap < <gv
xnoremap > >gv
set foldmethod=marker
nnoremap <space> za
set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'
Plugin 'zxqfl/tabnine-vim'
Plugin 'airblade/vim-gitgutter'
Plugin 'preservim/nerdtree'
Plugin 'mileszs/ack.vim'

Plugin 'flazz/vim-colorschemes'
Plugin 'gmarik/vundle'
Plugin 'tpope/vim-fugitive'
Plugin 'Lokaltog/vim-easymotion'
Plugin 'tpope/vim-rails.git'
Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}
Plugin 'L9'
Plugin 'FuzzyFinder'
Plugin 'tpope/vim-surround'
Plugin 'Command-T'
let g:NERDTreeDirArrowExpandable = '▸'
let g:NERDTreeDirArrowCollapsible = '▾'

let g:ackprg = 'ag --nogroup --nocolor --column'

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line
" et NERDTreeAutoCenter=1
let NERDTreeBookmarksFile=$VIM.'\Data\NerdBookmarks.txt'
let NERDTreeMouseMode=2
let NERDTreeShowBookmarks=1
let NERDTreeShowFiles=1
let NERDTreeShowHidden=1
let NERDTreeShowLineNumbers=1
let NERDTreeWinPos='left'
let NERDTreeWinSize=31
map <F5> :NERDTreeMirror<CR>
map <F5> :NERDTreeToggle<CR>

"surround.vim ack.vim
