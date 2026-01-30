#pragma once


namespace matplot {


    class figure_type;

    class axes_type;

	// axes_objects:
	class bars;
	class box_chart;
    class circles;
    class contours;
    class error_bar;
    class filled_area;
    class function_line;
    class histogram;
    class labels;
    class line;
    class matrix;
    class network;
    class parallel_lines;
    class stair;
    class string_function;
    class surface;
    class vectors;



    class visitor
	{
    public:
        virtual ~visitor() {}
        // figure
        virtual void visit(figure_type&) {};
        // axes
        virtual void visit(axes_type&) {};

        // axes_objects:
        virtual void visit(bars&) {};
        virtual void visit(box_chart&) {};
        virtual void visit(circles&) {};
        virtual void visit(contours&) {};
        virtual void visit(error_bar&) {};
        virtual void visit(filled_area&) {};
        virtual void visit(function_line&) {};
        virtual void visit(histogram&) {};
        virtual void visit(labels&) {};
        virtual void visit(class matplot::line&) {};
        virtual void visit(matrix&) {};
        virtual void visit(network&) {};
        virtual void visit(parallel_lines&) {};
        virtual void visit(stair&) {};
        virtual void visit(string_function&) {};
        virtual void visit(surface&) {};
        virtual void visit(vectors&) {};

	};

    #define MATPLOT_OBJECT_META  void accept(visitor& v) override { v.visit(*this); };

};