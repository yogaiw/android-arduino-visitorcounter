package com.hureyo.viscount.adapters

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import com.hureyo.viscount.R
import com.hureyo.viscount.model.Suhu
import kotlinx.android.synthetic.main.item_suhu.view.*

class SuhuAdapter (private val list: ArrayList<Suhu>): RecyclerView.Adapter<SuhuAdapter.SuhuViewHolder>() {
    inner class SuhuViewHolder(itemView: View): RecyclerView.ViewHolder(itemView) {
        fun bind(suhu : Suhu) {
            with(itemView) {
                tv_suhu.text = suhu.suhu.toString()
                tv_increment.text = "#" + (adapterPosition + 1).toString()
            }
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): SuhuViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(R.layout.item_suhu, parent, false)
        return SuhuViewHolder(view)
    }

    override fun onBindViewHolder(holder: SuhuViewHolder, position: Int) {
        holder.bind(list[position])
    }

    override fun getItemCount(): Int = list.size
}