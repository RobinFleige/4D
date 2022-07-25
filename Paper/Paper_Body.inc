% ---------------------------------------------------------------------
% EG author guidelines plus sample file for EG publication using LaTeX2e input
% D.Fellner, v2.03, Dec 14, 2018


\title[Meta Topology for Multi-Parameter-Dependent Vector Fields]%
      {Meta Topology for Multi-Parameter-Dependent Vector Fields}

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
%-------------------------------------------------------------------------
%-------------------------------------------------------------------------
%-------------------------------------------------------------------------
%-------------------------------------------------------------------------
%-------------------------------------------------------------------------
%-------------------------------------------------------------------------
%-------------------------------------------------------------------------
\section{Introduction}
% TODO Rework Others
Topological methods have become a standard tool in vector field visualization. Initially introduced as a visualization tool in, topological methods have been extended to higher order critical points, boundary switch points, and closed separatrices. In addition, topological methods have been applied to smooth, compress and model vector fields. The topology of 3D vector fields is visualized in.

% TODO Rework Others
The main idea of topological methods is to segment the domain into areas of different flow behavior. To do so, critical points are extracted and classified. Starting from saddle points, separation curves/surfaces are integrated. The union of critical points and separatrices is called topological skeleton. 

% TODO Rework Others
Concerning vector fields v(x,t), x $\in$ IRn depending on one parameter t (like e.g. time-dependent flows), critical points move with changing t. In fact, they form line structures in IRn+1. Furthermore, critical points might appear or disappear at some t. Those births and deaths of critical points are called fold bifurcations and their occurence changes the topological behavior of the field abruptly: two critical points of opposite index collapse and disappear (or the other way around: a critical point appears and splits up into two critical points immediately). Knowing the locations of these events is a key to understanding the dynamics of the data. Another important structural change is denoted by a spiraling source changing to a spiraling sink or vice versa. This is called a Hopf bifurcation. Other types of local bifurcations (Transcritical and Pitchfork bifurcation) are possible, but structurally unstable - we therefore do not treat them here.

% TODO Vector fields v(x, s,t)
% TODO Rework Others
Critical points move with changing s and t and form surface structures now. Consequently, bifurcation points move  as well and form line structures in IRn+2. This creates new types of structurally stable bifurcations: births and deaths of fold or Hopf bifurcations themselves. We call them fold-fold and Hopf-fold bifurcations. Those events are isolated points in IRn+2.

% TODO Rework Own
With increasing number of parameters the dimensionality of bifurcation structures increases and new structures emerge, birth and death of fold-fold and Hopf-fold bifurcations and recursively birth and death of these structures.

% TODO Rework Own
While the main interest of topology is to partition vector fields into regions of similar flow behavior, this paper will work on partitioning parameter-dependent vector fields into regions of similar vector fields via meta-topology.
For this purpose, the topology of a vector field is considered as a simple information and the focus is placed on the parameter field.
% Nicht nur Vector Fields
% Nicht nur Aufteilung (Separatritzen)

% TODO Rework Own
There are many use cases for multiparameter dependent vector fields in simulations. In flow simulations, parameters can describe the number, shape, or size of an object in the airflow. Also the strength, orientation and position of the source can be seen as parameters.
In electromagnetic fields, parameters define the position and strength of electromagnets.

The use case that inspired this work is that the parameters correspond to the electromagnets in an MRI.

% TODO
Recall Extraction of topological structures of One-parameter dependent vector fields in Research\\
% TODO
Feature Flow Field Approach

% TODO
Start with Two-Parameter, to Update Extraction/Classification/Behaviour/Properties in general way\\
% TODO
Improve Algorithm and Extraction/Classification/Behaviour/Properties for arbitrary parameters\\
% TODO
Since we only look for the parameter-space, the space-dimensions are arbitrary for this paper, but we use 2 for a better visualization\\

% TODO
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

Eingehen auf 2P2D Paper\\
Eingehen auf FFF und Stable FFF Paper\\
Eingehen auf 2-Bifurcation Buch\\
Recall 1P2D\\
Recall 2P2D\\
Recall FFF für 2P2D\\
Recall M-FFF für 2P2D\\
Recall 2-Bifurcation for 2P2D\\
Seeding in all Bifurcations and critical points on boundaries\\

Alles beschreiben und erläutern, was ich übernehmen will; \\
Einige Punkte die ich überarbeiten will ansprechen; \\
Dinge, die ich für falsch halte oder anders machen will überspringen\\


%-------------------------------------------------------------------------
\subsection{Critical points}
Quelle, Senke, Sattel, Bifurcation (degeneriert)\\

%-------------------------------------------------------------------------
\subsection{Parameter dependent vector fields}
Normalerweise Time Dependent\\
Bei mehreren Parametern eher Position, Orientierung, Stärke von Elektromagnet/Luftstrom/Wasserstrom\\

Unterschied in Vektorfeldeigenschaften von Luft, Wasser, Magnetfeld ausarbeiten\\

%-------------------------------------------------------------------------
\subsection{Feature flow field}
p n+1 dimensionale Vektorfelder, die Veränderung/Verschiebung von Vektorfeld entlang des Parameters beschreiben\\

Wird genbutzt um kritische Punkte entlang eines Parameters zu tracken\\

Lineare Näherung, nicht exakt\\

Orthogonal zu allen Gradienten\\

Ein FFF pro Parameter\\

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
Entstehung von zwei kritischen Punkten aus dem Nichts (Birth) oder auflösung zweier sich treffender kritischer Punkte (Death)\\

Hopf/Fold Bifurkation\\

%-------------------------------------------------------------------------
\subsection{Streamlines}
Integralkurve des stationären Feldes\\


%-------------------------------------------------------------------------
\subsection{Line of critical points from Bifurcation through parameter values}
Streamline über FFF mit Start in Bifurcation\\


%-------------------------------------------------------------------------
\subsection{Meta-Bifurcation/Fold-fold Bifurcations}
Bifurkation des angepassten Vektorfeldes ist Meta-Bifurkation des originalen Vektorfeldes\\

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
Streamline über M-FFF mit Start in M-Bifurcation\\

%-------------------------------------------------------------------------
\section{Two-Parameter-Dependent Vector Fields}

%-------------------------------------------------------------------------
\subsection{Meta Topology}
Anstatt sich die Topologie eines Vektorfeldes anzusehen, sehen wir uns hier die Topologie des Parameterfeldes an \\


%-------------------------------------------------------------------------
\subsection{Artificial Vectorfield}
Anpassung des originalen Vektorfeldes mit einer weiteren Komponente, die die Bifurkationsbedingung enthält\\

Kritischer Punkt des angepassten Vektorfeldes ist Bifurkation des originalen\\
%-------------------------------------------------------------------------
\subsection{Eigenschaften Bifurcation Curve}
Verhält sich im Parameterfeld wie Separatrix im Vektorfeld\\

Teilt Parameterfeld in Bereiche von Vektorfeldern mit identischer Topologie\\

Mehrere Bifurcatrion Curves können sich in Parameterprojektion schneiden\\



Meta-Bifurcation:
Es "entstehen" nicht wirklich 2 Bifurkationen an einer 2-Bifurkation; es entsteht eine 1-dimensionale Bifurkation; Das lässt sich daran erkennen, dass trotzdem nur 2 kritische Punkte existieren; Eine seite ist Birth, die andere Death, daher dazwischen 2 kritische Punkte\\

Classification:
BD Classification only works for single points on the bifurcation structure; \\
Instead have an inner/outer BD\\

Extraction:
Angepasste Extraktion über Seeding statt Ränder (Ränder sind n-1 dimensional; im 2P2D Paper nutzen sie analytisch berechnete Seeds; Auf angepasstem Feld wären Ränder kleiner, aber Vektorfelder entsprechend größer); \\
Kritische Punkte sind nicht unendlich stabil, daher werden sie irgendwann entstehen und irgendwann wieder verschwinden. Daher sollte in der Natur die Birth Seite immer im inneren der Bifurkation sein\\
Daher sollten alle Bifurkationen, die eine Ecke umschließen durch das Abtasten aller Ecken gefunden werden. Alle Bifurkationen können gefunden werden, wenn nur ein kritischer Punkt der zur Bifurkation gehört im inneren der Bifurkationsstruktur existiert\\

Visualization;Meta:
Fokus besonders auf der Meta-Ebene; Vereinfacht Visualisierung und gibt ähnlich viele Infos\\
Identische Topologie innerhalb eines Bereichs auf einer Seite von Bifurkationen\\


%-------------------------------------------------------------------------
\section{Multi-Parameter-Dependent Vector Fields}


Erweiterung der Bifurcations in beliebige Dimensionen
Allgemeines FFF in beliebigen Dimensionen
%-------------------------------------------------------------------------
\subsection{Bifurcation Manifold}
Stream-manifold über alle M-FFF mit Start in M-Bifurcation\\

Ein n-parameterabhängiges Vektorfeld besitzt n-1 dimensionale Bifurkationsstrukturen\\

Ein n-parameterabhängiges Vektorfeld besitzt n-1-a dimensionale Bifurkationsstrukturen von Grad a\\



%-------------------------------------------------------------------------
\section{Method}
%-------------------------------------------------------------------------
\section{Concept}
\subsection{Discretization}

%-------------------------------------------------------------------------
\section{Implementation}

%-------------------------------------------------------------------------
\subsection{Extraction}
Extraktion von Bifurcation Manifolds über Verfolgung von 1D Strukturen zu Strukturen höheren Grades\\

n-D field has 2*n (n-1)-D Oberflächen, diese werden schnell zu groß fürs Seede, stattdessen Random Seeds(Wahrscheinlichkeit berechnen, dass Strukturen über Größe x gefunden werden)\\

Analytical Solutions\\

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
