% ---------------------------------------------------------------------
% EG author guidelines plus sample file for EG publication using LaTeX2e input
% D.Fellner, v2.03, Dec 14, 2018


\title[Meta topology for multi-parameter dependent vector fields]%
      {Meta topology for multi-parameter dependent vector fields}

% for anonymous conference submission please enter your SUBMISSION ID
% instead of the author's name (and leave the affiliation blank) !!
% for final version: please provide your *own* ORCID in the brackets following \orcid; see https://orcid.org/ for more details.
\author[R. Fleige \& F. Sadlo]
{\parbox{\textwidth}{\centering R. Fleige$^1$\orcid{0000-0001-7756-0901}
        and F. Sadlo$^1$\orcid{0000-0001-5923-423X} }
        \\
% For Computer Graphics Forum: Please use the abbreviation of your first name.
{\parbox{\textwidth}{\centering $^1$Ruprecht -Karls-Universität Heidelberg, Germany\\}
}
}
% ------------------------------------------------------------------------

% if the Editors-in-Chief have given you the data, you may uncomment
% the following five lines and insert it here
%
% \volume{36}   % the volume in which the issue will be published;
% \issue{1}     % the issue number of the publication
% \pStartPage{1}      % set starting page


%-------------------------------------------------------------------------
\begin{document}



\maketitle
%-------------------------------------------------------------------------
\begin{abstract}
   The ABSTRACT is to be in fully-justified italicized text, 
   between two horizontal lines,
   in one-column format, 
   below the author and affiliation information. 
   Use the word ``Abstract'' as the title, in 9-point Times, boldface type, 
   left-aligned to the text, initially capitalized. 
   The abstract is to be in 9-point, single-spaced type.
   The abstract may be up to 3 inches (7.62 cm) long. \\
   Leave one blank line after the abstract, 
   then add the subject categories according to the ACM Classification Index 
%-------------------------------------------------------------------------
%  ACM CCS 1998
%  (see https://www.acm.org/publications/computing-classification-system/1998)
% \begin{classification} % according to https://www.acm.org/publications/computing-classification-system/1998
% \CCScat{Computer Graphics}{I.3.3}{Picture/Image Generation}{Line and curve generation}
% \end{classification}
%-------------------------------------------------------------------------
%  ACM CCS 2012
   (see https://www.acm.org/publications/class-2012)
%The tool at \url{http://dl.acm.org/ccs.cfm} can be used to generate
% CCS codes.
%Example:
\begin{CCSXML}
<ccs2012>
<concept>
<concept_id>10010147.10010371.10010352.10010381</concept_id>
<concept_desc>Computing methodologies~Collision detection</concept_desc>
<concept_significance>300</concept_significance>
</concept>
<concept>
<concept_id>10010583.10010588.10010559</concept_id>
<concept_desc>Hardware~Sensors and actuators</concept_desc>
<concept_significance>300</concept_significance>
</concept>
<concept>
<concept_id>10010583.10010584.10010587</concept_id>
<concept_desc>Hardware~PCB design and layout</concept_desc>
<concept_significance>100</concept_significance>
</concept>
</ccs2012>
\end{CCSXML}

\ccsdesc[300]{Computing methodologies~Collision detection}
\ccsdesc[300]{Hardware~Sensors and actuators}
\ccsdesc[100]{Hardware~PCB design and layout}


\printccsdesc   
\end{abstract}  
%-------------------------------------------------------------------------
\section{Introduction}

TODO
%-------------------------------------------------------------------------
\section{Related Works}
%http://www.isg.cs.uni-magdeburg.de/visual/files/publications/Archive/Weinkauf_2006_CGF.pdf
%http://wwwisg.cs.uni-magdeburg.de/visual/files/publications/Archive/Theisel_2003_VisSym.pdf
%http://isgwww.cs.uni-magdeburg.de/visual/files/publications/2010/weinkauf_2010_IEEE.pdf


\begin{figure}[htb]
\centering
\includegraphics[width=.8\linewidth]{2d2p_screenshot}
\parbox[t]{.9\columnwidth}
%
\caption{\label{fig:firstExample}
Bifurcation Curve instead of Bifurcation Point in 2P}
\end{figure}

%-------------------------------------------------------------------------
\section{Fundamentals}

\subsection{Critical points}
Quelle, Senke, Sattel, Bifurcation (degeneriert)
\subsection{Parameter dependent vector fields}
Normalerweise Time Dependent
Bei mehreren Parametern eher Position, Orientierung, Stärke von Elektromagnet/Luftstrom/Wasserstrom

Unterschied in Vektorfeldeigenschaften von Luft, Wasser, Magnetfeld ausarbeiten

\subsection{Feature flow field}
p n+1 dimensionale Vektorfelder, die Veränderung/Verschiebung von Vektorfeld entlang des Parameters beschreiben

Wird genbutzt um kritische Punkte entlang eines Parameters zu tracken

Lineare Näherung, nicht exakt

Orthogonal zu allen Gradienten

Ein FFF pro Parameter

Vektorfeld:
\begin{align}
\begin{pmatrix}x\\y\end{pmatrix}
\end{align}

FFF:
\begin{align}
\begin{pmatrix}\det(\Delta x_2,\Delta y_2)\\\det(\Delta y_2,\Delta t_2)\\\det(\Delta t_2,\Delta x_2)\end{pmatrix}
\end{align}


\subsection{Bifurcations}
Entstehung von zwei kritischen Punkten aus dem Nichts (Birth) oder auflösung zweier sich treffender kritischer Punkte (Death)

Hopf/Fold Bifurkation
\subsection{Streamlines}
Integralkurve des stationären Feldes
\subsection{Meta Topology}
Anstatt sich die Topologie eines Vektorfeldes anzusehen, sehen wir uns hier die Topologie des Parameterfeldes an 


\subsection{Line of critical points from Bifurcation through parameter values}
Streamline über FFF mit Start in Bifurcation


\subsection{Artificial Vectorfield}
Anpassung des originalen Vektorfeldes mit einer weiteren Komponente, die die Bifurkationsbedingung enthält

Kritischer Punkt des angepassten Vektorfeldes ist Bifurkation des originalen
\subsection{Meta-Bifurcation/Fold-fold Bifurcations}
Bifurkation des angepassten Vektorfeldes ist Meta-Bifurkation des originalen Vektorfeldes
\subsection{Meta-FFF/FFF for Tracking Fold Bifurcation}
FFF des angepassten Vektorfeldes ist Meta-FFF des originalen Vektorfeldes

Erweiterbar auf belkiebig viele Dimensionen

Originales Vektorfeld:
\begin{align}
\begin{pmatrix}x\\y\end{pmatrix}
\end{align}

FFF:
\begin{align}
\begin{pmatrix}\det(\Delta x_2,\Delta y_2)\\\det(\Delta y_2,\Delta t_2)\\\det(\Delta t_2,\Delta x_2)\end{pmatrix}
\end{align}

Umgewandeltes Vektorfeld:
\begin{align}
\begin{pmatrix}x\\y\\z = \det(\Delta x,\Delta y)\end{pmatrix}
\end{align}

Meta-FFF:
\begin{align}
\begin{pmatrix}\det(\Delta x_3,\Delta y_3,\Delta z_3)\\\det(\Delta y_3,\Delta z_3,\Delta s_3)\\\det(\Delta z_3,\Delta s_3,\Delta x_3)\\\det(\Delta s_3,\Delta x_3,\Delta y_3)\end{pmatrix} =
\begin{pmatrix}\det(\Delta x_3,\Delta y_3,\Delta \det(\Delta x_2,\Delta y_2))\\\det(\Delta y_3,\Delta \det(\Delta x_2,\Delta y_2),\Delta s_3)\\\det(\Delta \det(\Delta x_2,\Delta y_2),\Delta s_3,\Delta x_3)\\\det(\Delta s_3,\Delta x_3,\Delta y_3)\end{pmatrix}
\end{align}
\subsection{Bifurcation Curve}
Streamline über M-FFF mit Start in M-Bifurcation

\subsection{Bifurcation Manifold}
Stream-manifold über alle M-FFF mit Start in M-Bifurcation

Ein n-parameterabhängiges Vektorfeld besitzt n-1 dimensionale Bifurkationsstrukturen

Ein n-parameterabhängiges Vektorfeld besitzt n-1-a dimensionale Bifurkationsstrukturen von Grad a

\subsection{Eigenschaften Bifurcation Curve}
Verhält sich im Parameterfeld wie Separatrix im Vektorfeld

Teilt Parameterfeld in Bereiche von Vektorfeldern mit identischer Topologie

Mehrere Bifurcatrion Curves können sich in Parameterprojektion schneiden



%-------------------------------------------------------------------------
\section{Method}
%-------------------------------------------------------------------------
\section{Concept}
\subsection{Discretization}

%-------------------------------------------------------------------------
\section{Implementation}
\subsection{Extraction}
Extraktion von Bifurcation Manifolds über Verfolgung von 1D Strukturen zu Strukturen höheren Grades

n-D field has 2*n (n-1)-D Oberflächen, diese werden schnell zu groß fürs Seede, stattdessen Random Seeds(Wahrscheinlichkeit berechnen, dass Strukturen über Größe x gefunden werden)

\subsection{Analyzation}
Analyse des Vektorfeldes anhand der Strukturen höheren Grades

%-------------------------------------------------------------------------
\section{Results}




%-------------------------------------------------------------------------
\section{Type-style and fonts}


\ref{fig:firstExample}.

\noindent Long captions should be set as in Figure~\ref{fig:ex1} or
Figure~\ref{fig:ex3}.

\begin{figure}[htb]
   % an empty figure just consisting of the caption lines
   \caption{\label{fig:ex1}
     'Empty' figure only to serve as an example of long caption requiring 
     more than one line. It is not typed centered but aligned on both sides.}
\end{figure}

\noindent
Figures which need the full textwidth can be typeset as Figure~\ref{fig:ex3}.

\noindent Callouts should be 9-point Times, non-boldface type. Initially
capitalize only the first word of section titles and first-, second-, and
third-order headings.

FIRST-ORDER HEADINGS. (For example, \textbf{1. Introduction}) should be Times
9-point boldface, initially capitalized, flush left, with one blank line
before, and one blank line after.

SECOND-ORDER HEADINGS. (For example, \textbf{2.1. Language}) should be Times
9-point boldface, initially capitalized, flush left, with one blank line
before, and one after. If you require a third-order heading (we discourage
it), use 9-point Times, boldface, initially capitalized, flush left, preceded
by one blank line, followed by a period and your text on the same line.

The headline \emph{(authors / title)} must be shortened if it uses the full 
two column width of the main text.
There must be enough space for the page numbers. Please use ``et al.'' if 
there are more than three authors and specify a shortened version for your title.


%-------------------------------------------------------------------------
\subsection{References}

List all bibliographical references in 9-point Times, single-spaced, at the
end of your paper in alphabetical order. When referenced in the text, enclose
the citation index in square brackets, for example~\cite{Lous90}. Where
appropriate, include the name(s) of editors of referenced books.

For your references please use the following algorithm:
\begin{itemize} 
\item \textbf{one} author: first 3 chars plus year -- 
      e.g.\ \cite{Lous90}
\item \textbf{two}, \textbf{three} or \textbf{four} authors: first char
      of each family name plus year --  e.g.\ \cite{Fellner-Helmberg93} 
      or \cite{Kobbelt97-USHDR} or \cite{Lafortune97-NARF}
\item \textbf{more than 4} authors: first char of family name from 
      first 3 authors followed by a '*' followed by the year -- 
      e.g.\ \cite{Buhmann:1998:DCQ} or \cite{FolDamFeiHug.etal93} 
\end{itemize}

For BibTeX users a style file \ \texttt{eg-alpha.bst} and 
\texttt{eg-alpha-doi.bst} \ is available which uses the above algorithm.

For Biber users a style file \ \texttt{EG.bbx} \ is available which uses the above algorithm.
%  Store EG.bbx in the LaTeX distribution, for TeXLive in Windows: C:\texlive\2018\texmf-dist\tex\latex\biblatex\bbx  
%  and update filename database.
%-------------------------------------------------------------------------
\subsection{Illustrations, graphs, and photographs}

All graphics should be centered.

%%%
%%% Figure 1
%%%
\begin{figure}[htb]
  \centering
  % the following command controls the width of the embedded PS file
  % (relative to the width of the current column)
  \includegraphics[width=.8\linewidth]{sampleFig}
  % replacing the above command with the one below will explicitly set
  % the bounding box of the PS figure to the rectangle (xl,yl),(xh,yh).
  % It will also prevent LaTeX from reading the PS file to determine
  % the bounding box (i.e., it will speed up the compilation process)
  % \includegraphics[width=.95\linewidth, bb=39 696 126 756]{sampleFig}
  %
  \parbox[t]{.9\columnwidth}{\relax
           For all figures please keep in mind that you \textbf{must not}
           use images with transparent background! 
           }
  %
  \caption{\label{fig:firstExample}
           Here is a sample figure.}
\end{figure}

If your paper includes images, it is very important that they are of
sufficient resolution to be faithfully reproduced.

To determine the optimum size (width and height) of an image, measure
the image's size as it appears in your document (in millimeters), and
then multiply those two values by 12. The resulting values are the
optimum $x$ and $y$ resolution, in pixels, of the image. Image quality
will suffer if these guidelines are not followed.

Example 1: 
%
An image measures 50\,mm by 75\,mm when placed in a document. This
image should have a resolution of no less than 600 pixels by 900
pixels in order to be reproduced faithfully.

Example 2: 
%
Capturing a screenshot of your entire $1024 \times 768$ pixel display
monitor may be useful in illustrating a concept from your research. In
order to be reproduced faithfully, that $1024 \times 768$ image should
be no larger than 85 mm by 64 mm (approximately) when placed in your
document.


%-------------------------------------------------------------------------
\subsection{Color}

\textbf{Please observe:} as of 2003 publications in the proceedings of the
Eurographics Conference can use color images throughout the paper. No
separate color tables are necessary.

However, workshop proceedings might have different agreements! 
Figure~\ref{fig:ex3} is an example for creating color plates.

%------------------------------------------------------------------------
\subsection{Embedding of Hyperlinks / Typesetting of URLs}

Due to the use of the package \texttt{hyperref} the original behavior
of the command $\backslash$\texttt{url} from the package \texttt{url}
is not available. To circumvent this problem we either recommend to
use the command $\backslash$\texttt{httpAddr} from the 
included package \texttt{egweblnk} (see below) or to replace the
command $\backslash$\texttt{url} by the command $\backslash$\texttt{webLink} 
-- e.g. in cases where $\backslash$\texttt{url} has been used
widely in BibTeX-References. In the latter case we suggest to run
BibTeX as usual and then replace all occurences of $\backslash$\texttt{url}  by
$\backslash$\texttt{webLink}

\noindent
The provided commands for hyperlinks, in a nutshell, are:

\begin{description} \itemsep 1ex
\item [\webLinkFont $\backslash$httpAddr \{URL without leading 'http:'\}]
      \mbox{}\\
      e.g. \  \httpAddr{//diglib.eg.org/handle/10.2312/306}

\item [\webLinkFont $\backslash$httpsAddr \{URL without leading 'https:'\}]
      \mbox{}\\
      e.g. \  \httpsAddr{//diglib.eg.org/handle/10.2312/306}      

\item[\webLinkFont $\backslash$ftpAddr \{URL without leading 'ftp:'\}]
      \mbox{}\\
      e.g. \  \ftpAddr{//www.eg.org/EG/DL/ftpupload}   %

\item[\webLinkFont $\backslash$URL \{url\}]
      \mbox{}\\
      e.g. \  \URL{http://diglib.eg.org/handle/10.2312/306}

\item[\webLinkFont $\backslash$MailTo \{Email addr\}]
      \mbox{}\\
      e.g. \  \MailTo{publishing@eg.org}

\item[\webLinkFont $\backslash$MailToNA \{emailName\}\{@emailSiteAddress\}]
      \mbox{}\\
      e.g. \  \MailToNA{publishing}{@eg.org}

\item[\webLinkFont $\backslash$webLink\{URL without hyperlink creation\}]
      \mbox{}\\
      e.g. \  \webLink{http://www.eg.org/some_arbitrary_long/but_useless/URL}

\end{description}


%------------------------------------------------------------------------
\subsection{PDF Generation}

Your final paper should be delivered as a PDF document with all typefaces
embedded. \LaTeX{} users should use \texttt{dvips} and \texttt{ps2pdf} to
create this PDF document. Adobe Acrobat Distiller may be used in place of
\texttt{ps2pdf}.

Adobe PDFWriter is \emph{not} acceptable for use. Documents created with
PDFWriter will be returned to the author for revision. \texttt{pdftex} and
\texttt{pdflatex} (and its variants) can be used only if the author can
make certain that all typefaces are embedded and images are not downsampled
or subsampled during the PDF creation process.

Users with no access to these PDF creation tools should make available a
PostScript file and we will make a PDF document from it.


The PDF file \emph{must not} be change protected.

%------------------------------------------------------------------------
\subsubsection*{Configuration Notes: dvips / ps2pdf / etc.}

\noindent
\texttt{dvips} should be invoked with the \texttt{-Ppdf} and \texttt{-G0}
flags in order to use Type 1 PostScript typefaces:

\begin{verbatim}
    dvips -t a4 -Ppdf -G0 -o my.ps my.dvi
\end{verbatim}


\noindent
If you are using version 7.x of GhostScript, please use the following method of invoking \texttt{ps2pdf}, in
order to embed all typefaces and ensure that images are not downsampled or subsampled in the PDF
creation process:

\begin{verbatim}
  ps2pdf -dMaxSubsetPct=100 \
         -dCompatibilityLevel=1.3 \
         -dSubsetFonts=true \
         -dEmbedAllFonts=true \
         -dAutoFilterColorImages=false \
         -dAutoFilterGrayImages=false \
         -dColorImageFilter=/FlateEncode \
         -dGrayImageFilter=/FlateEncode \
         -dMonoImageFilter=/FlateEncode \
         mypaper.ps mypaper.pdf
\end{verbatim}


If you are using version 8.x of GhostScript, please use this method in place of the example above:
\begin{verbatim}
  ps2pdf -dPDFSETTINGS=/prepress \
         -dCompatibilityLevel=1.3 \
         -dAutoFilterColorImages=false \
         -dAutoFilterGrayImages=false \
         -dColorImageFilter=/FlateEncode \
         -dGrayImageFilter=/FlateEncode \
         -dMonoImageFilter=/FlateEncode \
         -dDownsampleColorImages=false \
         -dDownsampleGrayImages=false \
         mypaper.ps mypaper.pdf
\end{verbatim}

%------------------------------------------------------------------------
\subsubsection*{Configuration Notes: pdftex / pdflatex / etc.}

\noindent
Configuration of these tools to embed all typefaces can be accomplished by editing the \texttt{updmap.cfg} file
to enable inclusion of the standard (or base) 14 typefaces.

Linux users can run the \texttt{updmap} script to do this:
\begin{verbatim}
updmap --setoption pdftexDownloadBase14 true
\end{verbatim}

Windows users should edit the \texttt{updmap.cfg} files found in their TeX installation directories (one or both
of the following may be present):
\begin{verbatim}
  INSTALLDIR\texmf\web2c\updmap.cfg
  INSTALLDIR\localtexmf\miktex\config\updmap.cfg
\end{verbatim}

Ensure the value for \texttt{pdftexDownloadBase14} is "true," and then follow the instructions found here:
\httpAddr{//docs.miktex.org/manual/} to update your MikTeX installation.

%------------------------------------------------------------------------
\subsubsection*{Configuration Notes: Acrobat Distiller}

We recommend to use a Distiller job options file that embeds
all typefaces and does not downsample or subsample images when creating the PDF document.
%------------------------------------------------------------------------
\subsection{Exclusive License Form}

You must include your signed Eurographics Exclusive License Form 
when you submit your finished paper. We MUST have this form before
your paper can be published in the proceedings.

%-------------------------------------------------------------------------
\subsection{Conclusions}

Please direct any questions to the production editor in charge of
these proceedings.

%-------------------------------------------------------------------------
% bibtex
\bibliographystyle{eg-alpha-doi}
\bibliography{egbibsample}

% biblatex with biber
% \printbibliography                

%-------------------------------------------------------------------------
\newpage


\begin{figure*}[tbp]
  \centering
  \mbox{} \hfill
  % the following command controls the width of the embedded PS file
  % (relative to the width of the current column)
  \includegraphics[width=.3\linewidth]{sampleFig}
  % replacing the above command with the one below will explicitly set
  % the bounding box of the PS figure to the rectangle (xl,yl),(xh,yh).
  % It will also prevent LaTeX from reading the PS file to determine
  % the bounding box (i.e., it will speed up the compilation process)
  % \includegraphics[width=.3\linewidth, bb=39 696 126 756]{sampleFig}
  \hfill
  \includegraphics[width=.3\linewidth]{sampleFig}
  \hfill \mbox{}
  \caption{\label{fig:ex3}%
           For publications with color tables (i.e., publications not offering
           color throughout the paper) please \textbf{observe}: 
           for the printed version -- and ONLY for the printed
           version -- color figures have to be placed in the last page.
           \newline
           For the electronic version, which will be converted to PDF before
           making it available electronically, the color images should be
           embedded within the document. Optionally, other multimedia
           material may be attached to the electronic version. }
\end{figure*}

\end{document}
