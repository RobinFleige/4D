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
Topology Introduction as in 2P2D Paper

While the main interest of topology is to partition vector fields into regions of similar flow behavior, this paper will work on partitioning parameter-dependent vector fields into regions of similar vector fields via meta-topology.

One-Parameter dependent vector fields described(critical points form lines along t; fold bifurcations)
Two-Parameter dependent vector fields described in similar matter (critical points form planes; bifurcations form lines; 2-bifurcations exist)
Multi-Parameter dependent vector fields described

Anwendungsfälle/Auftauchen von Multi-Parameter dependent vector fields

Recall Extraction of topological structures of One-parameter dependent vector fields in Research
Feature Floe Field Approach

Start with Two-Parameter, to Update Extraction/Classification/Behaviour/Properties in general way
Improve Algorithm and Extraction/Classification/Behaviour/Properties for arbitrary parameters
Since we only look for the parameter-space, the space-dimensions are arbitrary for this paper, but we use 2 for a better visualization

Einleitung in die restlichen Kapitel


%-------------------------------------------------------------------------
\section{Related Works/Fundamentals}
%http://www.isg.cs.uni-magdeburg.de/visual/files/publications/Archive/Weinkauf_2006_CGF.pdf
%http://wwwisg.cs.uni-magdeburg.de/visual/files/publications/Archive/Theisel_2003_VisSym.pdf
%http://isgwww.cs.uni-magdeburg.de/visual/files/publications/2010/weinkauf_2010_IEEE.pdf
%https://www.fer.unizg.hr/_download/repository/Guckenheimer,_J._-_Nonlinear_Oscillations_Dynamical_Systems_and_Bifurcations_of_Vector_Fields_(1986).pdf

\begin{figure}[htb]
\centering
\includegraphics[width=.8\linewidth]{2d2p_screenshot}
\parbox[t]{.9\columnwidth}
%
\caption{\label{fig:firstExample}
Bifurcation Curve instead of Bifurcation Point in 2P}
\end{figure}

Eingehen auf 2P2D Paper
Eingehen auf FFF und Stable FFF Paper
Eingehen auf 2-Bifurcation Buch
Recall 1P2D
Recall 2P2D
Recall FFF für 2P2D
Recall M-FFF für 2P2D
Recall 2-Bifurcation for 2P2D
Seeding in all Bifurcations and critical points on boundaries

Alles beschreiben und erläutern, was ich übernehmen will; Einige Punkte die ich überarbeiten will ansprechen; Dinge, die ich für falsch halte oder anders machen will überspringen


%-------------------------------------------------------------------------
\subsection{Critical points}
Quelle, Senke, Sattel, Bifurcation (degeneriert)

%-------------------------------------------------------------------------
\subsection{Parameter dependent vector fields}
Normalerweise Time Dependent
Bei mehreren Parametern eher Position, Orientierung, Stärke von Elektromagnet/Luftstrom/Wasserstrom

Unterschied in Vektorfeldeigenschaften von Luft, Wasser, Magnetfeld ausarbeiten

%-------------------------------------------------------------------------
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


%-------------------------------------------------------------------------
\subsection{Bifurcations}
Entstehung von zwei kritischen Punkten aus dem Nichts (Birth) oder auflösung zweier sich treffender kritischer Punkte (Death)

Hopf/Fold Bifurkation

%-------------------------------------------------------------------------
\subsection{Streamlines}
Integralkurve des stationären Feldes


%-------------------------------------------------------------------------
\subsection{Line of critical points from Bifurcation through parameter values}
Streamline über FFF mit Start in Bifurcation


%-------------------------------------------------------------------------
\subsection{Meta-Bifurcation/Fold-fold Bifurcations}
Bifurkation des angepassten Vektorfeldes ist Meta-Bifurkation des originalen Vektorfeldes

%-------------------------------------------------------------------------
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

%-------------------------------------------------------------------------
\subsection{Bifurcation Curve}
Streamline über M-FFF mit Start in M-Bifurcation

%-------------------------------------------------------------------------
\section{Two-Parameter-Dependent Vector Fields}

%-------------------------------------------------------------------------
\subsection{Meta Topology}
Anstatt sich die Topologie eines Vektorfeldes anzusehen, sehen wir uns hier die Topologie des Parameterfeldes an 


%-------------------------------------------------------------------------
\subsection{Artificial Vectorfield}
Anpassung des originalen Vektorfeldes mit einer weiteren Komponente, die die Bifurkationsbedingung enthält

Kritischer Punkt des angepassten Vektorfeldes ist Bifurkation des originalen
%-------------------------------------------------------------------------
\subsection{Eigenschaften Bifurcation Curve}
Verhält sich im Parameterfeld wie Separatrix im Vektorfeld

Teilt Parameterfeld in Bereiche von Vektorfeldern mit identischer Topologie

Mehrere Bifurcatrion Curves können sich in Parameterprojektion schneiden



Meta-Bifurcation:
Es "entstehen" nicht wirklich 2 Bifurkationen an einer 2-Bifurkation; es entsteht eine 1-dimensionale Bifurkation; Das lässt sich daran erkennen, dass trotzdem nur 2 kritische Punkte existieren; Eine seite ist Birth, die andere Death, daher dazwischen 2 kritische Punkte

Classification:
BD Classification only works for single points on the bifurcation structure; 
Instead have an inner/outer BD

Extraction:
Angepasste Extraktion über Seeding statt Ränder (Ränder sind n-1 dimensional; im 2P2D Paper nutzen sie analytisch berechnete Seeds; Auf angepasstem Feld wären Ränder kleiner, aber Vektorfelder entsprechend größer); 
Kritische Punkte sind nicht unendlich stabil, daher werden sie irgendwann entstehen und irgendwann wieder verschwinden. Daher sollte in der Natur die Birth Seite immer im inneren der Bifurkation sein
Daher sollten alle Bifurkationen, die eine Ecke umschließen durch das Abtasten aller Ecken gefunden werden. Alle Bifurkationen können gefunden werden, wenn nur ein kritischer Punkt der zur Bifurkation gehört im inneren der Bifurkationsstruktur existiert

Visualization;Meta:
Fokus besonders auf der Meta-Ebene; Vereinfacht Visualisierung und gibt ähnlich viele Infos
Identische Topologie innerhalb eines Bereichs auf einer Seite von Bifurkationen


%-------------------------------------------------------------------------
\section{Multi-Parameter-Dependent Vector Fields}


Erweiterung der Bifurcations in beliebige Dimensionen
Allgemeines FFF in beliebigen Dimensionen
%-------------------------------------------------------------------------
\subsection{Bifurcation Manifold}
Stream-manifold über alle M-FFF mit Start in M-Bifurcation

Ein n-parameterabhängiges Vektorfeld besitzt n-1 dimensionale Bifurkationsstrukturen

Ein n-parameterabhängiges Vektorfeld besitzt n-1-a dimensionale Bifurkationsstrukturen von Grad a



%-------------------------------------------------------------------------
\section{Method}
%-------------------------------------------------------------------------
\section{Concept}
\subsection{Discretization}

%-------------------------------------------------------------------------
\section{Implementation}

%-------------------------------------------------------------------------
\subsection{Extraction}
Extraktion von Bifurcation Manifolds über Verfolgung von 1D Strukturen zu Strukturen höheren Grades

n-D field has 2*n (n-1)-D Oberflächen, diese werden schnell zu groß fürs Seede, stattdessen Random Seeds(Wahrscheinlichkeit berechnen, dass Strukturen über Größe x gefunden werden)

Analytical Solutions

%-------------------------------------------------------------------------
\subsection{Analyzation}
Analyse des Vektorfeldes anhand der Strukturen höheren Grades

%-------------------------------------------------------------------------
\section{Results}


%-------------------------------------------------------------------------
% bibtex
\bibliographystyle{eg-alpha-doi}
\bibliography{egbibsample}

% biblatex with biber
% \printbibliography                

%-------------------------------------------------------------------------
\newpage

%TODO: Schreibweise übernehmen: Two-Parameter-Dependent Vector Fields

\end{document}
